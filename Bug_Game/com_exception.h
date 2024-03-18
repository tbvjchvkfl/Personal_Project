#pragma once
#include <exception>
#include <winerror.h>
#include <stdio.h>
#include <string>

class com_exception : public std::exception
{
private:
	HRESULT result;
	std::string description;

public:
	com_exception(HRESULT hr) : result(hr), description() {}
	com_exception(HRESULT hr, std::string msg) : result(hr), description(msg) {}
	virtual const char* what() const override
	{
		static char str[512]{};
		sprintf_s(str, "Failed with HRESULT : %08X\n%s\n", result, description.c_str());
		return str;
	}
};

inline void ThrowIfFailed(HRESULT hr, std::string msg = "")
{
	if (FAILED(hr))
	{
		throw com_exception(hr, msg);
	}
}