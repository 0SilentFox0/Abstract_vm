# include "Commands.hpp"

Commands::Commands(): _counter(0){}
Commands::~Commands(){}

void    Commands::execute(std::list<std::string> &operands)
{
	for (std::list<std::string>::iterator i = operands.begin(); i != operands.end(); ++i)
	{
		this->_counter++;
		std::string line = *i;

		if (line.substr(0, line.find(" ")) == "push") { this->push(line); }
		if (line.substr(0, line.find(" ")) == "pop") {this->pop();}
		if (line.substr(0, line.find(" ")) == "dump") {this->dump();}
		if (line.substr(0, line.find(" ")) == "add") {this->add();}
		if (line.substr(0, line.find(" ")) == "sub") {this->sub();}
		if (line.substr(0, line.find(" ")) == "mul") {this->mul();}
		if (line.substr(0, line.find(" ")) == "div") {this->div();}
		if (line.substr(0, line.find(" ")) == "mod") {this->mod();}
		if (line.substr(0, line.find(" ")) == "print") {this->print();}
		if (line.substr(0, line.find(" ")) == "assert") {this->assert(line);}
	}
}

eOperandType        Commands::StringToType(std::string type)
{
    if (type == "int8(") {return _Int8;}
    if (type == "int16") {return _Int16;}
    if (type == "int32") {return _Int32;}
    if (type == "float") {return _Float;}
    return _Double;
}

///////////////////////
/////// Commands /////
/////////////////////

void    Commands::push(std::string line)
{
    std::string type = line.substr(line.find(' ') + 1, 5);
    std::string content = line.substr(line.find('(') + 1, line.size());
    this->_stack.push_front(this->_operands.createOperand(StringToType(type), content));
}

void        Commands::pop()
{
	if (!this->_stack.size())
	{
		std::cerr << YEL "Error on line -> " << this->_counter << "\n";
		throw Commands::EmptyStack();
	}
	else
		this->_stack.pop_front();
}


void              Commands::dump( void ) {
    if (!this->_stack.size()) 
	{
		std::cerr << YEL "Error on line -> " << this->_counter << "\n";
        throw Commands::EmptyStack();
    }
    for (std::list<IOperand const *>::iterator i = this->_stack.begin(); i != this->_stack.end(); ++i) {
        if ((*i)->getType() == _Float || (*i)->getType() == _Double) {
            std::cout << std::stold((*i)->toString()) << std::endl;
        } else {
           std::cout << std::stold((*i)->toString()) << std::endl;
        }
    }
}

void		Commands::add()
{
	 if (this->_stack.size() < 2)
	 {
		std::cerr << YEL "Error on line -> " << this->_counter << "\n";
		throw Commands::EmptyStack();
	 }
		IOperand const * a = *this->_stack.begin();
		this->_stack.pop_front();
		IOperand const * b = *this->_stack.begin();
		this->_stack.pop_front();
		IOperand const * sum = *a + *b;
		this->_stack.push_front(sum);
}

void		Commands::mul()
{
	 if (this->_stack.size() < 2)
	 {
		std::cerr << YEL "Error on line -> " << this->_counter << "\n";
		throw Commands::EmptyStack();
	 }
		IOperand const * a = *this->_stack.begin();
		this->_stack.pop_front();
		IOperand const * b = *this->_stack.begin();
		this->_stack.pop_front();
		IOperand const * sum = *a * *b;
		this->_stack.push_front(sum);
}

void		Commands::sub()
{
	 if (this->_stack.size() < 2)
	 {
		std::cerr << YEL "Error on line -> " << this->_counter << "\n";
		throw Commands::EmptyStack();
	 }
		IOperand const * a = *this->_stack.begin();
		this->_stack.pop_front();
		IOperand const * b = *this->_stack.begin();
		this->_stack.pop_front();
		IOperand const * sum = *a - *b;
		this->_stack.push_front(sum);
}

void		Commands::div()
{
	 if (this->_stack.size() < 2)
	 {
		std::cerr << YEL "Error on line -> " << this->_counter << "\n";
		throw Commands::EmptyStack();
	 }
		IOperand const * a = *this->_stack.begin();
		this->_stack.pop_front();
		IOperand const * b = *this->_stack.begin();
		this->_stack.pop_front();
		if (std::stold(a->toString()) == 0)
		{
			std::cerr << YEL "Error on line -> " << this->_counter << "\n";
			throw Commands::OperationWithZero();
		}
		IOperand const * sum = *b / *a;
		this->_stack.push_front(sum);
}

void		Commands::mod()
{
	 if (this->_stack.size() < 2)
	 {
		std::cerr << YEL "Error on line -> " << this->_counter << "\n";
		throw Commands::EmptyStack();
	 }
		IOperand const * a = *this->_stack.begin();
		this->_stack.pop_front();
		IOperand const * b = *this->_stack.begin();
		this->_stack.pop_front();
		if (std::stold(a->toString()) == 0)
		{
			std::cerr << YEL "Error on line -> " << this->_counter << "\n";
			throw Commands::OperationWithZero();
		}
		IOperand const * sum = *b % *a;
		this->_stack.push_front(sum);
}

void		Commands::print()
{
	 if (!this->_stack.size())
	 {
		std::cerr << YEL "Error on line -> " << this->_counter << "\n";
		throw Commands::EmptyStack();
	 }
	IOperand const * a = *this->_stack.begin();
	if (a->getType() != _Int8)
	{
		std::cerr << YEL "Error on line -> " << this->_counter << "\n";
		throw Commands::Not8Bit();
	}
	else
		std::cout << GREEN <<static_cast<char>(std::stoi(a->toString())) << FINISH;
}

void		Commands::assert(std::string line)
{
	if (!this->_stack.size())
	{
		std::cerr << YEL "Error on line -> " << this->_counter << "\n";
		throw Commands::EmptyStack();
	 }
	IOperand const * a = *this->_stack.begin();
	std::string type = line.substr(line.find(' ') + 1, 5);
    std::string content = line.substr(line.find('(') + 1, line.size());
	eOperandType aType = StringToType(type);
	if (aType != a->getType())
	{
		std::cerr << YEL "Error on line -> " << this->_counter << "\n";
		throw AssertProblem();
	}
	if (std::stold(content) != std::stold(a->toString()))
	{
		std::cerr << YEL "Error on line -> " << this->_counter << "\n";
		throw AssertProblem();
	}
}

///////////////////////////
//// Exceptions //////////
/////////////////////////

const char *Commands::EmptyStack::what() const throw() { 
	return (RED "Error: Not enough parameters or empty stack!");
}

const char *Commands::OperationWithZero::what() const throw() { 
	return (RED "Error: Don't joke with Zero!");
}

const char *Commands::Not8Bit::what() const throw() { 
	return (RED "Error: The value isn't an int8 type!");
}

const char *Commands::AssertProblem::what() const throw() { 
	return (RED "Error: Assert error -> the type or value is different!!");
}
