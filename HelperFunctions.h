#ifndef HEADER_HELPERFUNC
  #define HEADER_HELPERFUNC
   
  //Prototype for helper_function found in HelperFunctions.cpp
  void helper_function( void );
  void printHex(byte *buffer, byte bufferSize);
  void printDec(byte *buffer, byte bufferSize);
  void byte2HexStr(byte array[], unsigned int len, char buffer[]);
#endif
