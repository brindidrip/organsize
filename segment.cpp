/*segment.cpp*/

#include "segment.h"

Segment::Segment(long long seq, long long sig, long long totSeg, std::vector<unsigned char> data, long long index)
    : sequenceNum(seq), signature(sig), totalSegments(totSeg), segmentData(data), index(index)
{ }