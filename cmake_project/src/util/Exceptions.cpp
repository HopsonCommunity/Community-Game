//
// Created by jakub on 02.04.17.
//

#include "Exceptions.h"

namespace Exceptions
{
    ExceptionBase::ExceptionBase(const std::string& text)
    : m_msg(text)
    {
    }

    const char* ExceptionBase::what() const throw()
    {
        return m_msg.c_str();
    }


    CannotGetResource::CannotGetResource(const std::string& full) : ExceptionBase(std::string("Cannot get resource: "))
    {
        m_msg += full;
    }
}
