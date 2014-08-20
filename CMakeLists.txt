cmake_minimum_required (VERSION 2.6)
project ( Mass_Effect_Save_Extractor )

set ( source_files src/SaveExtract src/RWHelper src/BinFile src/BitArray src/MEShared src/ME3Format )

add_executable (SaveExtract ${source_files})
