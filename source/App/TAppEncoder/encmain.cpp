/* The copyright in this software is being made available under the BSD
 * License, included below. This software may be subject to other third party
 * and contributor rights, including patent rights, and no such rights are
 * granted under this license.
 *
 * Copyright (c) 2010-2015, ITU/ISO/IEC
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *  * Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *  * Neither the name of the ITU/ISO/IEC nor the names of its contributors may
 *    be used to endorse or promote products derived from this software without
 *    specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

/** \file     encmain.cpp
    \brief    Encoder application main
*/
#include <nvToolsExtCuda.h>
#include <nvToolsExtCudaRt.h>
#include <time.h>
#include <sys/time.h>
#include <iostream>
#include "TAppEncTop.h"
#include "TAppCommon/program_options_lite.h"
#include <cuda_runtime.h>
//! \ingroup TAppEncoder
//! \{

#include "../Lib/TLibCommon/Debug.h"

// ====================================================================================================================
// Main function
// ====================================================================================================================
//extern Double dTotalIntMeTime; //JCY
//extern Double dTotalSubIntMeTime; //JCY
//extern Double dTotalBiRefIntMeTime; //JCY


int main(int argc, char* argv[])
{
  TAppEncTop  cTAppEncTop;
  nvtxNameOsThreadA(pthread_self(),"MAIN");
  cudaSetDevice(1); //JCY global switch device

  // print information
  fprintf( stdout, "\n" );
  fprintf( stdout, "HM software: Encoder Version [%s] (including RExt)", NV_VERSION );
  fprintf( stdout, NVM_ONOS );
  fprintf( stdout, NVM_COMPILEDBY );
  fprintf( stdout, NVM_BITS );
  fprintf( stdout, "\n\n" );

  // create application encoder class
  cTAppEncTop.create();

  // parse configuration
  try
  {
    if(!cTAppEncTop.parseCfg( argc, argv ))
    {
      cTAppEncTop.destroy();
#if ENVIRONMENT_VARIABLE_DEBUG_AND_TEST
      EnvVar::printEnvVar();
#endif
      return 1;
    }
  }
  catch (df::program_options_lite::ParseFailure &e)
  {
    std::cerr << "Error parsing option \""<< e.arg <<"\" with argument \""<< e.val <<"\"." << std::endl;
    return 1;
  }

#if PRINT_MACRO_VALUES
  printMacroSettings();
#endif

#if ENVIRONMENT_VARIABLE_DEBUG_AND_TEST
  EnvVar::printEnvVarInUse();
#endif

 // starting time
    Double dResult;
    struct timeval start, end;

    //clock_t lBefore = clock();
    gettimeofday(&start,NULL);
    // call encoding function
    cTAppEncTop.encode();
    gettimeofday(&end,NULL);

    // ending time
    //dResult = (Double)(clock()-lBefore) / CLOCKS_PER_SEC;
    dResult = (end.tv_sec - start.tv_sec);
    dResult += (end.tv_usec - start.tv_usec) / 1000000.0;
    printf("\n Total Time: %12.3f sec.\n", dResult);
  //printf("\n Total Integer ME: %12.3f sec.\n", dTotalIntMeTime);
  //printf("\n Total Sub-Integer ME: %12.3f sec.\n", dTotalSubIntMeTime);
  //printf("\n Total Bi-refinement ME: %12.3f sec.\n", dTotalBiRefIntMeTime);

  // destroy application encoder class
  cTAppEncTop.destroy();

  return 0;
}

//! \}
