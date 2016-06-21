#include <iostream>
#include <fstream>
#include <math.h>
#include <string>

int main (int argc, char *argv[]) {
	if(argc >= 2) {
		std::fstream inputFile;
		std::fstream bitmapFile;
		std::string fileName = argv[1];
		std::string outputFile = fileName + ".bmp";
		bitmapFile.open(outputFile.c_str(),std::ios::in|std::ios::binary|std::ios::out|std::ios::trunc);
		inputFile.open(argv[1],std::ios::in|std::ios::binary|std::ios::out);
		std::streampos begin,end;
		begin = inputFile.tellg();
		inputFile.seekg(0,std::ios::end);
		end = inputFile.tellg();
		inputFile.seekg(0,std::ios::beg);
		int inputFileSize = (end-begin);
		int rootNumber = ceil(inputFileSize/3);
		int additionValue = 0;
		double currentCalculatedValue = sqrt(rootNumber+additionValue);
		int bitmapWidth;
		bool imageSizeFound = false;
		while(!imageSizeFound) {
			currentCalculatedValue = sqrt(rootNumber+additionValue);
			if(ceil(currentCalculatedValue)-currentCalculatedValue == 0) {
				bitmapWidth = (int)currentCalculatedValue;
				imageSizeFound = true;
			} else {
				additionValue = additionValue + 1;
			}
		}
		int bitmapHeight = bitmapWidth;
		int bitmapFileSize = (bitmapHeight*bitmapWidth*3)+54+ (bitmapHeight * 2);
		int bitmapDataSize = inputFileSize + (bitmapHeight * 2);
		int extraPixles = (bitmapHeight*bitmapWidth*3)-inputFileSize;
		char * extramem = new char [extraPixles];
		char bitmapFileHeader[14] = {'B','M',bitmapFileSize & 0xFF,(bitmapFileSize >> 8) & 0xFF,(bitmapFileSize >> 16) & 0xFF,(bitmapFileSize >> 24) & 0xFF,0,0,0,0,54,0,0,0};
		char bitmapInfoHeader[40] = {40,0,0,0,bitmapWidth & 0xFF,(bitmapWidth >> 8) & 0xFF,(bitmapWidth >> 16) & 0xFF,(bitmapWidth >> 24) & 0xFF,bitmapHeight & 0xFF,(bitmapHeight >> 8) & 0xFF,(bitmapHeight >> 16) & 0xFF,(bitmapHeight >> 24) & 0xFF,1,0,24,0,0,0,0,0,bitmapDataSize & 0xFF,(bitmapDataSize >> 8) & 0xFF,(bitmapDataSize >> 16) & 0xFF,(bitmapDataSize >> 24) & 0xFF,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
		char * memblock = new char [end];
		inputFile.read(memblock,end);
		inputFile.close();
		bitmapFile.write(bitmapFileHeader,14);
		bitmapFile.write(bitmapInfoHeader,40);
		//bitmapFile.write(memblock,end);
		//bitmapFile.write(extramem,extraPixles);
		/*
		char buffer[6];
		for(int cpimb = 0;cpimb<end/3;cpimb = cpimb + 1) {
			buffer[0] = memblock[cpimb];
			buffer[1] = memblock[cpimb+1];
			buffer[2] = memblock[cpimb+2];
			buffer[3] = 0;
			buffer[4] = 0;
			buffer[5] = 0;
			bitmapFile.write(buffer,5);
		}
		for(int cpiem = 0;cpiem<extraPixles/3;cpiem = cpiem + 1) {
			buffer[0] = extramem[cpiem];
			buffer[1] = extramem[cpiem+1];
			buffer[2] = extramem[cpiem+2];
			buffer[3] = 0;
			buffer[4] = 0;
			buffer[5] = 0;
			bitmapFile.write(buffer,5);
		}
		*/
		
		char * totalmem = new char[(end+extraPixles)];
		for(int ccbmb = 0;ccbmb<end;ccbmb=ccbmb+1) {
			totalmem[ccbmb] = memblock[ccbmb];
		}
		for(int ccbem = 0;ccbem<extraPixles;ccbem=ccbem+1) {
			totalmem[ccbem+end] = extramem[ccbem];
		}
		//strcpy(totalmem,memblock);
		//strcat(totalmem,extramem);
		char * rowBuffer = new char[2];
		rowBuffer[0] = 0;
		rowBuffer[1] = 0;
		char * currentBytes = new char[3];
		for(int chib=0;chib<bitmapHeight;chib=chib+1) {
			for(int cwib=0;cwib<bitmapWidth;cwib=cwib+1) {
				currentBytes[0] = totalmem[((chib*bitmapWidth*3)+(cwib*3))];
				currentBytes[1] = totalmem[((chib*bitmapWidth*3)+(cwib*3))+1];
				currentBytes[2] = totalmem[((chib*bitmapWidth*3)+(cwib*3))+2];
				bitmapFile.write(currentBytes,3);
			}
			bitmapFile.write(rowBuffer,2);
		}
		
		std::cout << argv[1] << std::endl;
		std::cout << "inputFileSize:" << inputFileSize << std::endl;
		std::cout << "bitmapHeight:" << bitmapHeight << std::endl;
		std::cout << "extraPixles:" << extraPixles << std::endl;
		std::cout << "bitmapFileSize:" << bitmapFileSize << std::endl;
		std::cout << "bitmapDataSize:" << bitmapDataSize << std::endl;
		bitmapFile.close();
		delete[] totalmem;
		delete[] rowBuffer;
		delete[] currentBytes;
		delete[] extramem;
		delete[] memblock;
		return 0;
	} else {
		std::cout << "Usage: fileToBitmap.exe <file>" << std::endl;
		return 0;
	}
}