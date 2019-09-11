#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include "Operands.hpp"

template <typename T>
class Functions: public IOperand
{
public:
	Functions(){};
	~Functions(){};
	Functions(Functions const &copy)
	{
		this->_content = copy._content;
		this->_string = copy._string;
		this->_type = copy._type;
	}

	Functions(std::string content, eOperandType type) : _content(content), _type(type), _numb(std::stold(content))
	{
		 long double val = std::stold(content);
		 if (checker<long double>(val, type))
			throw OverUnderFlow();
	}

	int		getPrecision() const  override
	{
		return (static_cast<int>(this->_type));
	}

	eOperandType		getType() const  override
	{
		return (this->_type);
	}

	std::string const &toString() const override
	{
		return (this->_content);
	}

	const IOperand *operator-(IOperand const &rhs) const override
 	{
 	 Operands   ret;
 	 eOperandType type = std::max(this->_type, rhs.getType());
 	 //exeption managment
 	 return type < _Float
 	     ? ret.createOperand(type, std::to_string(_numb - std::stoi(rhs.toString())))
 	     : ret.createOperand(type, std::to_string(_numb -  std::stod(rhs.toString())));
 	}

	const IOperand *operator+(IOperand const &rhs) const override
 	{
 	 Operands   ret;
 	 eOperandType type = std::max(this->_type, rhs.getType());
 	 //exeption managment
 	 return type < _Float
 	     ? ret.createOperand(type, std::to_string(_numb + std::stoi(rhs.toString())))
 	     : ret.createOperand(type, std::to_string(_numb + std::stod(rhs.toString())));
 	}
	
	const IOperand *operator*(IOperand const &rhs) const override
 	{
 	 Operands   ret;
 	 eOperandType type = std::max(this->_type, rhs.getType());
 	 //exeption managment
 	 return type < _Float
 	     ? ret.createOperand(type, std::to_string(_numb * std::stoi(rhs.toString())))
 	     : ret.createOperand(type, std::to_string(_numb *  std::stod(rhs.toString())));
 	}

	const IOperand *operator/(IOperand const &rhs) const override
 	{
 	 Operands   ret;
 	 eOperandType type = std::max(this->_type, rhs.getType());
 	 //exeption managment
 	 return type < _Float
 	     ? ret.createOperand(type, std::to_string(_numb / std::stoi(rhs.toString())))
 	     : ret.createOperand(type, std::to_string(_numb /  std::stod(rhs.toString())));
 	}

	const IOperand *operator%(IOperand const &rhs) const override
 	{
 	 Operands   ret;
 	 eOperandType type = std::max(this->_type, rhs.getType());
 	 //exeption managment
 	 return type < _Float
 	     ? ret.createOperand(type, std::to_string(_numb / std::stoi(rhs.toString())))
 	     : ret.createOperand(type, std::to_string(_numb /  std::stod(rhs.toString())));
 	}

	template <typename A>bool	checker(A content, eOperandType type) const
	{
		switch (type)
		{
		case (_Int8):
			return (content > INT8_MAX || content < INT8_MIN);
		case (_Int16):
			return (content > INT16_MAX || content < INT16_MIN);
		case (_Int32):
			return (content > INT32_MAX || content < INT32_MIN);
		case (_Float):
			return (content > FLT_MAX || content < FLT_MIN);
		case (_Double):
			return (!(content <= std::numeric_limits<double>::max() && content >= -std::numeric_limits<double>::max()));
		}
		return (true);
	}

	class OverUnderFlow : public std::exception
	{
		virtual const char * what() const throw()
		{
			return ("Error: Overflow / Underflow error!\n");
		}
	};
private:

	std::string		_content;
 	eOperandType	_type;
	T const			_numb;
};

#endif