/*segment.h*/

#include <vector>

class Segment
{
public:
    // data members:
    long long sequenceNum;
    long long signature;
    long long totalSegments;
    long long index;
    std::vector<unsigned char> segmentData;
    
    // constructor:
    Segment(long long sequence, long long signature, long long totalSegments, std::vector<unsigned char> segmentData, long long index);

    // member functions:

};