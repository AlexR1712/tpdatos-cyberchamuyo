/*
 * TextRecoveryUtilities.h
 *
 *  Created on: 21/11/2012
 *      Author: sebastian
 */

#ifndef TEXTRECOVERYUTILITIES_H_
#define TEXTRECOVERYUTILITIES_H_

#include "../include/BinaryArray2.h"
#include "../include/common.h"
#include "../include/binaryInputSequentialFile.h"
#include "../include/binaryOutputSequentialFile.h"
#include "../include/binaryDictionaryRecord.h"
#include "../include/DispersionEx.h"
#include "../include/Frase.h"

namespace TextRecoveryUtilities {

void cargarArchivosTerminos(Hash::DispersionEx F, BinaryOutputSequentialFile<BinaryDictionaryRecord<true> >& T, BinaryOutputSequentialFile<BinaryDictionaryRecord<true> >& termInDocFile);

BinaryArray2 gammaEncode(unsigned long n);

unsigned int gammaDecode(BinaryArray2 array, unsigned int pos = 0);

unsigned int gammaSize(unsigned int n);

}


#endif /* TEXTRECOVERYUTILITIES_H_ */
