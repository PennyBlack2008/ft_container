#ifndef _FUNCTEXCEPT_HPP_
#define _FUNCTEXCEPT_HPP_

#include <exception>
#include <string>

namespace ft {
	class runtime_error : public std::exception {
		private:
			std::string msg;
		public:
			explicit runtime_error(const std::string& arg);
			virtual ~runtime_error() throw();
			virtual const char* what() const throw();
	};

	class range_error : public runtime_error {
		public:
			explicit range_error(const std::string& arg);
	};

	class overflow_error : public runtime_error {
		public:
			explicit overflow_error(const std::string& arg);
	};

	class underflow_error : public runtime_error {
		public:
			explicit underflow_error(const std::string& arg);
	};

	void throw_range_error(const char*) __attribute__((__noreturn__));
}

#endif