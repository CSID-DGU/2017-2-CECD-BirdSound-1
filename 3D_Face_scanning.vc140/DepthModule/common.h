#pragma once
#include <iostream>
class notImplemented_error : public std::logic_error
{
public:
	notImplemented_error() : std::logic_error("기능이 아직 구현되지 않았습니다.") { };
};