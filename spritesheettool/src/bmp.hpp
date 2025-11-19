#ifndef BMP_HPP
#define BMP_HPP

#include <vector>

class BMP {
public:
    BMP() :
        m_signature         ( 19778 ),
        m_fileSize			( 122 ),
	    m_reserved			( 0 ),
	    m_dataOffset		( 122 ),
    	m_size				( 108 ),
    	m_width				( 0 ),
    	m_height			( 0 ),
    	m_planes			( 1 ),
    	m_bitsPerPixel		( 32 ),
    	m_compression		( 3 ),
    	m_imageSize			( 0 ),
    	m_xPixelsPerM		( 0 ),
    	m_yPixelsPerM		( 0 ),
    	m_colorsUsed		( 0 ),
    	m_importantColors	( 0 ),
        m_lcsWindowsColorSpace ( 0 ),
        m_redGamma ( 0 ),
        m_greenGamma ( 0 ),
        m_blueGamma ( 0 ),
        m_bitMasks ( {255, 65280, 16711680, 4278190080} )
    {}

    struct BitMasks {
		unsigned int m_red;
		unsigned int m_green;
		unsigned int m_blue;
		unsigned int m_alpha;
	};

    short m_signature;
	int m_fileSize;
	int m_reserved;
	int m_dataOffset;

	int m_size;
	int m_width;
	int m_height;
	short m_planes;
	short m_bitsPerPixel;
	int m_compression;
	int m_imageSize;
	int m_xPixelsPerM;
	int m_yPixelsPerM;
	int m_colorsUsed;
	int m_importantColors;

    BitMasks m_bitMasks;

    int m_lcsWindowsColorSpace;
	char m_ciexyzEndpoints[36] = { 0 };
	int m_redGamma;
	int m_greenGamma;
	int m_blueGamma;

    std::vector<char> m_pixelData;
};

#endif