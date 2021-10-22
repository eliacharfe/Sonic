#pragma once

class Exception : public std::exception
{
public:
	Exception(const char* str)  : m_str(str) {}
    Exception(string str, int i) : m_string(str + to_string(i) + '\n') 
    {
        m_str = &m_string[0];
    }
	const char* what() const noexcept { return m_str; }

private:
	const char* m_str;
    string m_string;
};
//--------------------------------------------------------------------------
struct UnknownCollision : public std::runtime_error
{
//public:
    UnknownCollision(GameObject& a, GameObject& b)
        : std::runtime_error(string("Unknown collision of ")
            + typeid(a).name() + " and " + typeid(b).name())
    { }

//private:
};