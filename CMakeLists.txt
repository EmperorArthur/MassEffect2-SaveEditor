cmake_minimum_required (VERSION 2.6)
project ( Mass_Effect_Save_Extractor )

set ( source_files SaveExtract RWHelper BinFile BitArray MEShared ME3Format )

add_executable (SaveExtract ${source_files})
