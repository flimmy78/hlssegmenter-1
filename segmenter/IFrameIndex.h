/*
 * IFrameIndex.h
 *
 *  Created on: Aug 8, 2014
 *      Author: satram
 */

#ifndef IFRAMEINDEX_H_
#define IFRAMEINDEX_H_

#include "segmenterCommon.h"


class decision_flags
{
	bool idr_size_calculated;
	std::pair<bool,bool> update_iframe_playlist; //pair of do and done
	bool chunk_start;
	std::pair<bool,bool> update_media_playlist; //pair of do and done
public:
	decision_flags()
	{
		idr_size_calculated = false;
		update_iframe_playlist = std::pair<bool,bool>(false, false);
		chunk_start = false;
		update_media_playlist = std::pair<bool,bool>(false, false);
	}
	~decision_flags() {};
	friend class IFrameIndex;
	friend class HlsPlaylistGenerator;
	friend class Segmenter;
};


class IFrameIndex {

	int total_pkt_count;
	long long total_byte_offset;
	long long dts;
	int idr_size;
	int chunk_size;
	double duration_from_last_idr;
	double duration_from_chunk_start;

	decision_flags flags;
public:
	IFrameIndex(int count, long long timestamp, long long byte_offset);
	virtual ~IFrameIndex();
	void update(int count, long long timestamp, long long byte_offset);
	void finalize(int count, long long timestamp, long long byte_offset);
	void start_chunk();
	void finalize_chunk(int count, long long timestamp, long long byte_offset);
	friend class Segmenter;
};

#endif /* IFRAMEINDEX_H_ */