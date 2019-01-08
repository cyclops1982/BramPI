#pragma once

#include <iostream>
#include <exception>

using namespace std;


// From https://stackoverflow.com/questions/8152720/correct-way-to-inherit-from-stdexception
class BramPIException : public std::exception
{
public:
	/** Constructor (C strings).
	*  @param message C-style string error message.
	*                 The string contents are copied upon construction.
	*                 Hence, responsibility for deleting the char* lies
	*                 with the caller. 
	*/
	explicit BramPIException(const char* message): reason(message) {
	}

	/** Constructor (C++ STL strings).
	*  @param message The error message.
	*/
	explicit BramPIException(const std::string& message): reason(message) {
	}

	/** Destructor.
	* Virtual to allow for subclassing.
	*/
	virtual ~BramPIException() throw() {
	}

	/** Returns a pointer to the (constant) error description.
	*  @return A pointer to a const char*. The underlying memory
	*          is in posession of the Exception object. Callers must
	*          not attempt to free the memory.
	*/
	virtual const char* what() const throw() {
		return reason.c_str();
	}

private:
	std::string reason;
};
