// Blip
// Copyright (c) Xettex 2016

/// \file
/// \brief Contains the \ref main function
/// \ingroup application

#include "blip/application.hpp"

/// \addtogroup application
/// \{

/// \brief The entry point of the program
/// \return exit status of the program
int main()
{
    return blip::application{}.run();
}

/// \}
