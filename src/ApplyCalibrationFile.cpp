//////////////////////////////////////////////////////////////////////////////////
// Applies calibration file to analysis tree
//
// Author:        Connor Natzke (cnatzke@triumf.ca)
// Creation Date: 2023-05-09 10:18:46
// Last Update:
// Usage:
//
//////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "TGRSIUtilities.h"
#include "TParserLibrary.h"
#include "TEnv.h"
#include "TFile.h"
// #include "TChannel.h"

#include "ApplyCalibrationFile.h"

int main(int argc, char **argv)
{

    if (argc == 1)
    { // no inputs given
        PrintUsage(argv);
        return 0;
    }

    InitGRSISort();

    const char *analysis_file = argv[1];
    const char *calibration_file = argv[2];

    TFile input_file(analysis_file, "read");
    TChannel::ReadCalFile(calibration_file);
    TChannel::WriteToRoot();
    input_file.Close();

    return 0;

} // main

/******************************************************************************
 * Initializes GRSISort libraries and stuff
 *
 *****************************************************************************/
void InitGRSISort()
{
    // makes time retrival happy and loads GRSIEnv
    grsi_path = getenv("GRSISYS");
    if (grsi_path.length() > 0)
    {
        grsi_path += "/";
    }
    grsi_path += ".grsirc";
    gEnv->ReadFile(grsi_path.c_str(), kEnvChange);

    TParserLibrary::Get()->Load();
} // end InitGRSISort

/******************************************************************************
 * Prints usage message and version
 *****************************************************************************/
void PrintUsage(char *argv[])
{
    std::cerr << argv[0] << "\n"
              << "usage: " << argv[0] << " analysis_tree calibration_file\n"
              << " analysis_tree:          analysis tree\n"
              << " calibration_file:       calibration file"
              << std::endl;
} // end PrintUsage