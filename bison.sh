flex -c++ --outfile=src/assembler/gblexer.cpp src/assembler/gblexer.l
bison -v --output-file=src/assembler/gbparser.cpp src/assembler/gbparser.ypp