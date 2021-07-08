#include "..\stdafx.h"
#include <vector>

#ifndef dsf_types_h
#define dsf_types_h

/* Based on "DSF File Format Specification, Version 1.01" from Sony Corporation */

#pragma pack(push, 1)

#define DSF_SIGNATURE_DSD_	0x20445344	// 'DSD '
#define DSF_HEADER_SIZE		28

typedef struct {
	uint32_t DSD_;						// 'D', 'S', 'D', ' '
	uint64_t size;						// 28
	uint64_t file_size;					// overall file size
	uint64_t id3v2_pointer;				// offset to id3v2 metadata chunk
} DSF_HEADER;

#define DSF_fmt_SIZE		52

#define DSF_FORMAT_VERSION	1

#define DSF_FMTID_RAW		0			// DSD raw

#define DSF_CHTYPE_MONO		1			// 1 : Center
#define DSF_CHTYPE_STEREO	2			// 1 : Front Left 2 : Front Right
#define DSF_CHTYPE_3CHS		3			// 1 : Front Left 2 : Front Right 3 : Center
#define DSF_CHTYPE_QUAD		4			// 1 : Front Left 2 : Front Right 3 : Back Left 4 : Back Right
#define DSF_CHTYPE_4CHS		5			// 1 : Front Left 2 : Front Right 3 : Center 4 : Low Frequency
#define DSF_CHTYPE_5CHS		6			// 1 : Front Left 2 : Front Right 3 : Center 4 : Back Left 5 : Back Right
#define DSF_CHTYPE_5_1CHS	7			// 1 : Front Left 2 : Front Right 3 : Center 4 : Low Frequency 5 : Back Left 6 : Back Right

#define DSD_FREQ_64FS	( 2822400)		// = 44100 * 64
#define DSD_FREQ_128FS	( 5644800)		// = 44100 * 128
#define DSD_FREQ_256FS	(11289600)		// = 44100 * 256

#define DSF_BPS_LSB		1				// LSb first
#define DSF_BPS_MSB		8				// MSb first

#define DSF_BLOCK_SIZE_PER_CHANNEL	4096
#define DSF_RESERVED	0

#define DSF_SIGNATURE_fmt_	0x20746d66	// 'fmt '

typedef struct {
	uint32_t fmt_;						// 'f', 'm', 't', ' '
	uint64_t size;						// 52
	uint32_t format_version;			// 1, DSF_FORMAT_VERSION
	uint32_t format_id;					// DSF_FMTID_*
	uint32_t channel_type;				// layout of speakers and interleaved samples, DSF_CHTYPE_*
	uint32_t channel_num;				// # of channels
	uint32_t sampling_frequency;		// 2822400 (DSD64), 5644800 (DSD128)
	uint32_t bits_per_sample;			// 1 or 8, DSF_BPS_*
	uint64_t sample_count;				// sampling_frequency * seconds
	uint32_t block_size_per_channel;	// 4096
	uint32_t reserved;					// 0
} DSF_fmt_HEADER;

#define DSF_SIGNATURE_data	0x61746164	// 'data'
#define DSF_data_SIZE		12

typedef struct {
	uint32_t data;						// 'd', 'a', 't', 'a'
	uint64_t size;
	// here comes data
} DSF_data_HEADER;

#pragma pack(pop)

#endif // !dsf_types_h


#ifndef dff_types_h
#define dff_types_h

#pragma pack(push, 1)


#define DSD_FREQ_64FS	( 2822400)		// = 44100 * 64
#define DSD_FREQ_128FS	( 5644800)		// = 44100 * 128

typedef uint32_t DFFID;

#define MAKE_DFFID(a, b, c, d)		(((((((a) << 8) | (b)) << 8) | (c)) << 8) | (d))
#define MAKE_DFFID_S(s)				(MAKE_DFFID(s[0], s[1], s[2], s[3]))

#define DFFID_FRM8					(MAKE_DFFID('F', 'R', 'M', '8'))
#define DFFID_DSD_					(MAKE_DFFID('D', 'S', 'D', ' '))
#define DFFID_FVER					(MAKE_DFFID('F', 'V', 'E', 'R'))
#define DFFID_PROP					(MAKE_DFFID('P', 'R', 'O', 'P'))
#define DFFID_SND_					(MAKE_DFFID('S', 'N', 'D', ' '))
#define DFFID_FS__					(MAKE_DFFID('F', 'S', ' ', ' '))
#define DFFID_CHNL					(MAKE_DFFID('C', 'H', 'N', 'L'))

// channel ids in CHNL
#define CHID_SLFT					(MAKE_DFFID('S', 'L', 'F', 'T'))
#define CHID_SRGT					(MAKE_DFFID('S', 'R', 'G', 'T'))
#define CHID_MLFT					(MAKE_DFFID('M', 'L', 'F', 'T'))
#define CHID_MRGT					(MAKE_DFFID('M', 'R', 'G', 'T'))
#define CHID_LS__					(MAKE_DFFID('L', 'S', ' ', ' '))
#define CHID_RS__					(MAKE_DFFID('R', 'S', ' ', ' '))
#define CHID_C___					(MAKE_DFFID('C', ' ', ' ', ' '))
#define CHID_LFE_					(MAKE_DFFID('L', 'F', 'E', ' '))

#define DFFID_CMPR					(MAKE_DFFID('C', 'M', 'P', 'R'))
#define CMPR_ID_DSD_				(MAKE_DFFID('D', 'S', 'D', ' '))
#define CMPR_ID_DST_				(MAKE_DFFID('D', 'S', 'T', ' '))
#define CMPR_NAME_DSD				"not compressed"
#define CMPR_NAME_DST				"DST Encoded"

#define DFFID_ABSS					(MAKE_DFFID('A', 'B', 'S', 'S'))
#define DFFID_LSCO					(MAKE_DFFID('L', 'S', 'C', 'O'))

#define LSCFG_STEREO				0
#define LSCFG_5CH_BS775_1			3
#define	LSCFG_6CH_BS775_1_LFE		4
#define LSCFG_UNDEFINED				65535

#define DFFID_DSD_					(MAKE_DFFID('D', 'S', 'D', ' '))
#define DFFID_DST_					(MAKE_DFFID('D', 'S', 'T', ' '))
#define DFFID_FRTE					(MAKE_DFFID('F', 'R', 'T', 'E'))

#define DST_FRAMES_PER_SECOND		75

#define DFFID_DSTF					(MAKE_DFFID('D', 'S', 'T', 'F'))
#define DFFID_DSTC					(MAKE_DFFID('D', 'S', 'T', 'C'))
#define DFFID_DSTI					(MAKE_DFFID('D', 'S', 'T', 'I'))
#define DFFID_COMT					(MAKE_DFFID('C', 'O', 'M', 'T'))

#define CMTTYPE_GENERAL				0
#define CMTTYPE_CHANNEL				1
#define CMTTYPE_SOURCE				2
#define CMTTYPE_HISTORY				3

#define CMTREF_GENERAL				0
#define CMTREF_CHANNEL_ALL			0
#define CMTREF_SOURCE_DSD			0
#define CMTREF_SOURCE_ANALOG		1
#define CMTREF_SOURCE_PCM			2
#define CMTREF_HISTORY_GENERAL		0
#define CMTREF_HISTORY_OPERATOR		1
#define CMTREF_HISTORY_MACHINE		2
#define CMTREF_HISTORY_TIMEZONE		3
#define CMTREF_HISTORY_REVISION		4

#define DFFID_DIIN					(MAKE_DFFID('D', 'I', 'I', 'N'))
#define DFFID_EMID					(MAKE_DFFID('E', 'M', 'I', 'D'))
#define DFFID_MARK					(MAKE_DFFID('M', 'A', 'R', 'K'))

#define MARKTYPE_TRACKSTART			0
#define MARKTYPE_TRACKSTOP			1
#define MARKTYPE_PROGRAMSTART		2
#define MARKTYPE_OBSOLETE			3
#define MARKTYPE_INDEX				4

#define MARKCH_ALL					0

#define DFFID_DIAR					(MAKE_DFFID('D', 'I', 'A', 'R'))
#define DFFID_DITI					(MAKE_DFFID('D', 'I', 'T', 'I'))
#define DFFID_MANF					(MAKE_DFFID('M', 'A', 'N', 'F'))

#include "CID3v2.h"
#include <stdlib.h>
#define SZ_KMP_TAGINFO_NAME_TITLE       "title"    //曲名
#define SZ_KMP_TAGINFO_NAME_ARTIST      "artist"   //アーティスト
#define SZ_KMP_TAGINFO_NAME_ALBUM       "album"    //アルバム
#define SZ_KMP_TAGINFO_NAME_GENRE       "genre"    //ジャンル
#define SZ_KMP_TAGINFO_NAME_DATE        "date"     //日付
#define SZ_KMP_TAGINFO_NAME_COMMENT     "comment"  //コメント
#define SZ_KMP_TAGINFO_NAME_ALBUMARTIST "albumartist" //アルバムアーティスト
#define SZ_KMP_TAGINFO_NAME_BITRATE     "bitrate"     //ビットレート
#define SZ_KMP_TAGINFO_NAME_TRACKNUMBER "tracknumber" //トラック番号
#define SZ_KMP_TAGINFO_NAME_DISCNUMBER  "discnumber"  //ディスク番号
#define SZ_KMP_TAGINFO_NAME_TRACKTOTAL  "tracktotal"  //トラック数
#define SZ_KMP_TAGINFO_NAME_DISCTOTAL   "disctotal"   //ディスク数
#define SZ_KMP_TAGINFO_NAME_REPLAYGAIN_TRACKGAIN "replaygain_track_gain" //リプレイゲイン
#define SZ_KMP_TAGINFO_NAME_REPLAYGAIN_TRACKPEAK "replaygain_track_peak" //リプレイゲイン
#define SZ_KMP_TAGINFO_NAME_REPLAYGAIN_ALBUMGAIN "replaygain_album_gain" //リプレイゲイン
#define SZ_KMP_TAGINFO_NAME_REPLAYGAIN_ALBUMPEAK "replaygain_album_peak" //リプレイゲイン

#pragma pack(push, 1)

#define WSD_FILEID			"1bit"
#define WSD_FORMAT_VERSION	0x11

#define DSD_FREQ_64FS	( 2822400)		// = 44100 * 64
#define DSD_FREQ_128FS	( 5644800)		// = 44100 * 128

__inline uint64_t ntohllX(uint64_t be)
{
	uint8_t* p = (uint8_t*)&be;
	uint64_t r = p[4];

	r = (r << 8) | p[5];
	r = (r << 8) | p[6];
	r = (r << 8) | p[7];
	r = (r << 8) | p[0];
	r = (r << 8) | p[1];
	r = (r << 8) | p[2];
	r = (r << 8) | p[3];

	return r;
}



__inline uint32_t ntohl(uint32_t be)
{
	uint8_t* p = (uint8_t*)&be;
	uint32_t r = p[0];

	r = (r << 8) | p[1];
	r = (r << 8) | p[2];
	r = (r << 8) | p[3];

	return r;
}

typedef struct {
	uint8_t		fileID[4];
	uint32_t	reserved1_1;
	uint8_t		version;
	uint8_t		reserved1_2;
	uint16_t	reserved1_3;
	uint64_t	fileSize;
	uint32_t	textOffset;
	uint32_t	dataOffset;
	uint32_t	reserved1_4;
} WSD_GENERAL_INFO;

typedef struct {
	uint32_t	playbackTime;
	uint32_t	samplingFrequency;
	uint32_t	reserved1_1;
	uint8_t		channels;
	uint8_t		reserved1_2[3];
	uint32_t	channelAssignment;
	uint8_t		reserved1_3[12];
	uint32_t	emphasis;
	uint32_t	reserved1_4;
	uint64_t	timeReferenceHi;
	uint64_t	timeReferenceLo;
	uint8_t		reserved1_5[40];
} WSD_DATA_SPEC;

typedef struct {
	uint8_t		title[128];
	uint8_t		composer[128];
	uint8_t		songWriter[128];
	uint8_t		artist[128];
	uint8_t		album[128];
	uint8_t		genre[32];
	uint8_t		dateAndTime[32];
	uint8_t		location[32];
	uint8_t		comment[512];
	uint8_t		userSpecific[512];
	uint8_t		reserved2[160];
} WSD_TEXT;

#pragma pack(pop)

#pragma pack(push, 1)

#include <stdint.h>
#include <vector>

#define DSD_FREQ_64FS	( 2822400)		// = 44100 * 64
#define DSD_FREQ_128FS	( 5644800)		// = 44100 * 128

typedef uint32_t DFFID;

#define MAKE_DFFID(a, b, c, d)		(((((((a) << 8) | (b)) << 8) | (c)) << 8) | (d))
#define MAKE_DFFID_S(s)				(MAKE_DFFID(s[0], s[1], s[2], s[3]))

#define DFFID_FRM8					(MAKE_DFFID('F', 'R', 'M', '8'))
#define DFFID_DSD_					(MAKE_DFFID('D', 'S', 'D', ' '))
#define DFFID_FVER					(MAKE_DFFID('F', 'V', 'E', 'R'))
#define DFFID_PROP					(MAKE_DFFID('P', 'R', 'O', 'P'))
#define DFFID_SND_					(MAKE_DFFID('S', 'N', 'D', ' '))
#define DFFID_FS__					(MAKE_DFFID('F', 'S', ' ', ' '))
#define DFFID_CHNL					(MAKE_DFFID('C', 'H', 'N', 'L'))

// channel ids in CHNL
#define CHID_SLFT					(MAKE_DFFID('S', 'L', 'F', 'T'))
#define CHID_SRGT					(MAKE_DFFID('S', 'R', 'G', 'T'))
#define CHID_MLFT					(MAKE_DFFID('M', 'L', 'F', 'T'))
#define CHID_MRGT					(MAKE_DFFID('M', 'R', 'G', 'T'))
#define CHID_LS__					(MAKE_DFFID('L', 'S', ' ', ' '))
#define CHID_RS__					(MAKE_DFFID('R', 'S', ' ', ' '))
#define CHID_C___					(MAKE_DFFID('C', ' ', ' ', ' '))
#define CHID_LFE_					(MAKE_DFFID('L', 'F', 'E', ' '))

#define DFFID_CMPR					(MAKE_DFFID('C', 'M', 'P', 'R'))
#define CMPR_ID_DSD_				(MAKE_DFFID('D', 'S', 'D', ' '))
#define CMPR_ID_DST_				(MAKE_DFFID('D', 'S', 'T', ' '))
#define CMPR_NAME_DSD				"not compressed"
#define CMPR_NAME_DST				"DST Encoded"

#define DFFID_ABSS					(MAKE_DFFID('A', 'B', 'S', 'S'))
#define DFFID_LSCO					(MAKE_DFFID('L', 'S', 'C', 'O'))

#define LSCFG_STEREO				0
#define LSCFG_5CH_BS775_1			3
#define	LSCFG_6CH_BS775_1_LFE		4
#define LSCFG_UNDEFINED				65535

#define DFFID_DSD_					(MAKE_DFFID('D', 'S', 'D', ' '))
#define DFFID_DST_					(MAKE_DFFID('D', 'S', 'T', ' '))
#define DFFID_FRTE					(MAKE_DFFID('F', 'R', 'T', 'E'))

#define DST_FRAMES_PER_SECOND		75

#define DFFID_DSTF					(MAKE_DFFID('D', 'S', 'T', 'F'))
#define DFFID_DSTC					(MAKE_DFFID('D', 'S', 'T', 'C'))
#define DFFID_DSTI					(MAKE_DFFID('D', 'S', 'T', 'I'))
#define DFFID_COMT					(MAKE_DFFID('C', 'O', 'M', 'T'))

#define CMTTYPE_GENERAL				0
#define CMTTYPE_CHANNEL				1
#define CMTTYPE_SOURCE				2
#define CMTTYPE_HISTORY				3

#define CMTREF_GENERAL				0
#define CMTREF_CHANNEL_ALL			0
#define CMTREF_SOURCE_DSD			0
#define CMTREF_SOURCE_ANALOG		1
#define CMTREF_SOURCE_PCM			2
#define CMTREF_HISTORY_GENERAL		0
#define CMTREF_HISTORY_OPERATOR		1
#define CMTREF_HISTORY_MACHINE		2
#define CMTREF_HISTORY_TIMEZONE		3
#define CMTREF_HISTORY_REVISION		4

#define DFFID_DIIN					(MAKE_DFFID('D', 'I', 'I', 'N'))
#define DFFID_EMID					(MAKE_DFFID('E', 'M', 'I', 'D'))
#define DFFID_MARK					(MAKE_DFFID('M', 'A', 'R', 'K'))

#define MARKTYPE_TRACKSTART			0
#define MARKTYPE_TRACKSTOP			1
#define MARKTYPE_PROGRAMSTART		2
#define MARKTYPE_OBSOLETE			3
#define MARKTYPE_INDEX				4

#define MARKCH_ALL					0

#define DFFID_DIAR					(MAKE_DFFID('D', 'I', 'A', 'R'))
#define DFFID_DITI					(MAKE_DFFID('D', 'I', 'T', 'I'))
#define DFFID_MANF					(MAKE_DFFID('M', 'A', 'N', 'F'))

struct DFFChunkHeader
{
	DFFID		ckID;
	uint64_t	ckDataSize;
};


uint64_t htonll(uint64_t val) {
	return (((uint64_t)htonl(val)) << 32) + htonl(val >> 32);
}

uint64_t ntohll(uint64_t val) {
	return (((uint64_t)(val)) << 32) + (val >> 32);
}

struct DFFChunk
{
	DFFChunkHeader	header;
	uint64_t		offsetToData;

	void setupHeader()
	{
		header.ckID = ntohl(header.ckID);
		header.ckDataSize = ntohll(header.ckDataSize);
	}

	virtual void setupData() {}
	uint64_t OffsetToData() const { return offsetToData; }
	DFFID ID() const { return header.ckID; }
	uint64_t DataSize() const { return header.ckDataSize; }
};

struct FVERChunk : public DFFChunk
{
	struct
	{
		uint32_t	version;
	} data;

	void setupData()
	{
		data.version = ntohl(data.version);
	}
};

struct FSChunk : public DFFChunk
{
	struct
	{
		uint32_t	sampleRate;
	} data;

	void setupData()
	{
		data.sampleRate = ntohl(data.sampleRate);
	}
};

struct CHNLChunk : public DFFChunk
{
	struct
	{
		uint16_t	numChannels;
	} data;

	std::vector<DFFID> chID;

	void setupData()
	{
		data.numChannels = ntohs(data.numChannels);
	}
};

struct CMPRChunk : public DFFChunk
{
	struct
	{
		DFFID		compressionType;
		uint8_t		count;
	} data;

	std::string	compressionName;

	void setupData()
	{
		data.compressionType = ntohl(data.compressionType);
	}
};

struct ABSSChunk : public DFFChunk
{
	struct
	{
		uint16_t	hours;
		uint8_t		minutes;
		uint8_t		seconds;
		uint32_t	samples;
	} data;

	void setupData()
	{
		data.hours = ntohs(data.hours);
		data.samples = ntohl(data.samples);
	}
};

struct LSCOChunk : public DFFChunk
{
	struct
	{
		uint16_t	lsConfig;
	} data;

	void setupData()
	{
		data.lsConfig = ntohs(data.lsConfig);
	}
};

struct PROPChunk : public DFFChunk
{
	struct
	{
		DFFID		propType;
	} data;

	FSChunk		fs;
	CHNLChunk	chnl;
	CMPRChunk	cmpr;
	ABSSChunk	abss;
	LSCOChunk	lsco;

	void setupData()
	{
		data.propType = ntohl(data.propType);
	}
};

struct DSDChunk : public DFFChunk
{
	// dsd sample data
};

struct FRTEChunk : public DFFChunk
{
	struct
	{
		uint32_t	numFrames;
		uint16_t	frameRate;
	} data;

	void setupData()
	{
		data.numFrames = ntohl(data.numFrames);
		data.frameRate = ntohs(data.frameRate);
	}
};

struct DSTFChunk : public DFFChunk
{
	// dst frame data
};

struct DSTCChunk : public DFFChunk
{
	struct
	{
		uint32_t	crc;
	} data;

	void setupData()
	{
		data.crc = ntohl(data.crc);
	}
};

struct DSTChunk : public DFFChunk
{
	struct
	{
	} data;

	FRTEChunk	frte;
	DSTFChunk	dstf;
	DSTCChunk	dstc;
};


struct DSTFrameIndex;

struct DSTIChunk : public DFFChunk
{
	struct
	{
	} data;

	std::vector<DSTFrameIndex> indexData;
};

struct DSTFrameIndex
{
	struct
	{
		uint64_t	offset;
		uint32_t	length;
	} data;

	void setupData()
	{
		data.offset = ntohll(data.offset);
		data.length = ntohl(data.length);
	}
};

struct Comment;

struct COMTChunk : public DFFChunk
{
	struct
	{
		uint16_t	numComments;
	} data;

	std::vector<Comment> comments;

	void setupData()
	{
		data.numComments = ntohs(data.numComments);
	}
};


struct Comment
{
	struct
	{
		uint16_t	timeStampYear;
		uint8_t		timeStampMonth;
		uint8_t		timeStampDay;
		uint8_t		timeStampHour;
		uint8_t		timeStampMinutes;
		uint16_t	cmtType;
		uint16_t	cmtRef;
		uint32_t	count;
	} data;

	std::string commentText;

	void setupData()
	{
		data.timeStampYear = ntohs(data.timeStampYear);
		data.cmtType = ntohs(data.cmtType);
		data.cmtRef = ntohs(data.cmtRef);
		data.count = ntohl(data.count);
	}
};

struct EMIDChunk : public DFFChunk
{
	struct
	{
	} data;

	std::string	emid;
};

struct MARKChunk : public DFFChunk
{
	struct
	{
		uint16_t	hours;
		uint8_t		minutes;
		uint8_t		seconds;
		uint32_t	samples;
		int32_t		offset;
		uint16_t	markType;
		uint16_t	markChannel;
		uint16_t	trackFlags;
		uint32_t	count;
	} data;

	std::string	markerText;

	void setupData()
	{
		data.hours = ntohs(data.hours);
		data.samples = ntohl(data.samples);
		data.offset = ntohl((uint32_t)data.offset);
		data.markType = ntohs(data.markType);
		data.markChannel = ntohs(data.markChannel);
		data.trackFlags = ntohs(data.trackFlags);
		data.count = ntohl(data.count);
	}
};

struct DIARChunk : public DFFChunk
{
	struct
	{
		uint32_t	count;
	} data;

	std::string	artistText;

	void setupData()
	{
		data.count = ntohl(data.count);
	}
};

struct DITIChunk : public DFFChunk
{
	struct
	{
		uint32_t	count;
	} data;

	std::string	titleText;

	void setupData()
	{
		data.count = ntohl(data.count);
	}
};

struct DIINChunk : public DFFChunk
{
	struct
	{
	} data;

	EMIDChunk	emid;
	MARKChunk	mark;
	DIARChunk	diar;
	DITIChunk	diti;
};

struct MANFChunk : public DFFChunk
{
	struct
	{
		DFFID		manID;
	} data;

	void setupData()
	{
		data.manID = ntohl(data.manID);
	}
};

struct FRM8Chunk : public DFFChunk
{
	struct
	{
		DFFID		formType;
	} data;

	FVERChunk	fver;
	PROPChunk	prop;
	DSDChunk	dsd;
	DSTChunk	dst;
	DSTIChunk	dsti;
	COMTChunk	comt;
	DIINChunk	diin;
	MANFChunk	manf;

	void setupData()
	{
		data.formType = ntohl(data.formType);
	}
};


#pragma pack(pop)



#pragma pack(pop)

#endif // !dff_types_h

#ifndef wsd_types_h
#define wsd_types_h

#include <stdint.h>

#pragma pack(push, 1)

#define WSD_FILEID			"1bit"
#define WSD_FORMAT_VERSION	0x11

#define DSD_FREQ_64FS	( 2822400)		// = 44100 * 64
#define DSD_FREQ_128FS	( 5644800)		// = 44100 * 128


#pragma pack(pop)

#endif // !wsd_types_h


/*
* SACD Decoder plugin
* Copyright (c) 2011-2020 Maxim V.Anisiutkin <maxim.anisiutkin@gmail.com>
*
* This program is free software; you can redistribute it and/or
* modify it under the terms of the GNU Lesser General Public
* License as published by the Free Software Foundation; either
* version 2.1 of the License, or (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
* Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public
* License along with FFmpeg; if not, write to the Free Software
* Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
*/

#pragma once

//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------

class CAbstractKpi
{
public:
	virtual BOOL Open(LPWSTR cszFileName, SOUNDINFO* pInfo, ULONGLONG& dwTagSize) = 0;
	virtual void Close() = 0;
	virtual DWORD Render(BYTE* buffer, DWORD dwSize) = 0;
	virtual DWORD SetPosition(DWORD dwPos) = 0;

	static BOOL GetTagInfo(const char *cszFileName, IKmpTagInfo *pInfo)
	{
		return FALSE;
	}
};



class CLargeFile
{
protected:
	HANDLE			hFile;
	LARGE_INTEGER	liFileSize;

public:
	CLargeFile();
	virtual ~CLargeFile();

	virtual BOOL Open(LPCWSTR szFileName);
	virtual void Close();

	virtual void Reset() { Seek(0, NULL, FILE_BEGIN); }

	HANDLE File() const { return hFile; }
	uint64_t FileSize() const { return liFileSize.QuadPart; }

	BOOL Seek(uint64_t distance, uint64_t* newPos, DWORD moveMethod) const
	{
		LARGE_INTEGER lidist, newpos = { 0 };
		BOOL r;

		lidist.QuadPart = (long long)distance;
		r = ::SetFilePointerEx(hFile, lidist, &newpos, moveMethod);
		if (newPos != NULL) *newPos = newpos.QuadPart;
		return r;
	}
	uint64_t Tell() const
	{
		LARGE_INTEGER zero = { 0 };

		::SetFilePointerEx(hFile, zero, &zero, FILE_CURRENT);
		return (uint64_t)zero.QuadPart;
	}

	BOOL Read(LPVOID buffer, DWORD bytesToRead, LPDWORD bytesRead) const
	{
		return ::ReadFile(hFile, buffer, bytesToRead, bytesRead, NULL);
	}

	uint64_t ntohllX(uint64_t be) const
	{
		uint8_t* p = (uint8_t*)&be;
		uint64_t r = p[4];

		r = (r << 8) | p[5];
		r = (r << 8) | p[6];
		r = (r << 8) | p[7];
		r = (r << 8) | p[0];
		r = (r << 8) | p[1];
		r = (r << 8) | p[2];
		r = (r << 8) | p[3];

		return r;
	}

	uint64_t ntohll(uint64_t be) const
	{
		uint8_t* p = (uint8_t*)&be;
		uint64_t r = p[0];

		r = (r << 8) | p[1];
		r = (r << 8) | p[2];
		r = (r << 8) | p[3];
		r = (r << 8) | p[4];
		r = (r << 8) | p[5];
		r = (r << 8) | p[6];
		r = (r << 8) | p[7];

		return r;
	}

	uint32_t ntohl(uint32_t be) const
	{
		uint8_t* p = (uint8_t*)&be;
		uint32_t r = p[0];

		r = (r << 8) | p[1];
		r = (r << 8) | p[2];
		r = (r << 8) | p[3];

		return r;
	}

	uint16_t ntohs(uint16_t be) const
	{
		uint8_t* p = (uint8_t*)&be;
		return (p[0] << 8) | p[1];
	}
};

CLargeFile::CLargeFile() : hFile(INVALID_HANDLE_VALUE)
{
	liFileSize.QuadPart = 0;
}

CLargeFile::~CLargeFile()
{
	Close();
}

void CLargeFile::Close()
{
	if (hFile != INVALID_HANDLE_VALUE)
	{
		::CloseHandle(hFile);
		hFile = INVALID_HANDLE_VALUE;
	}
}

BOOL CLargeFile::Open(LPCWSTR szFileName)
{
	hFile = ::CreateFile(szFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
		return FALSE;

	::GetFileSizeEx(hFile, &liFileSize);

	return TRUE;
}




class CDSFFile : public CLargeFile
{
private:
	DSF_HEADER header;
	DSF_fmt_HEADER fmt_header;
	DSF_data_HEADER data_header;

	uint64_t dataOffset;

	BOOL checkHeader();
public:
	CDSFFile();
	~CDSFFile();

	BOOL Open(LPCWSTR szFileName);
	void Close();

	void Reset();

	DSF_HEADER* Header() { return &header; }
	DSF_fmt_HEADER* FmtHeader() { return &fmt_header; }
	DSF_data_HEADER* DataHeader() { return &data_header; }
	uint64_t DataOffset() const { return dataOffset; }
};


CDSFFile::CDSFFile() : CLargeFile(), dataOffset(0)
{
}

CDSFFile::~CDSFFile()
{
	CLargeFile::~CLargeFile();
}

void CDSFFile::Close()
{
	CLargeFile::Close();
}

BOOL CDSFFile::Open(LPCWSTR szFileName)
{
	if (!CLargeFile::Open(szFileName))
		return FALSE;

	if (!checkHeader())
	{
		Close();
		return FALSE;
	}

	dataOffset = Tell();

	Reset();

	return TRUE;
}

BOOL CDSFFile::checkHeader()
{
	DWORD dwBytesRead;
	const DWORD DSD_ = DSF_SIGNATURE_DSD_, fmt_ = DSF_SIGNATURE_fmt_, data = DSF_SIGNATURE_data;

	{
		if (!Read(&header, sizeof header, &dwBytesRead))
			return FALSE;
		if (dwBytesRead != sizeof header)
			return FALSE;
		if (memcmp(&header.DSD_, &DSD_, sizeof header.DSD_) != 0)
			return FALSE;
		if (header.size != DSF_HEADER_SIZE)
			return FALSE;
		if (header.file_size != liFileSize.QuadPart)
			return FALSE;
	}
	{
		if (!Read(&fmt_header, sizeof fmt_header, &dwBytesRead))
			return FALSE;
		if (dwBytesRead != sizeof fmt_header)
			return FALSE;
		if (memcmp(&fmt_header.fmt_, &fmt_, sizeof fmt_header.fmt_) != 0)
			return FALSE;
		if (fmt_header.size != DSF_fmt_SIZE)
			return FALSE;
		if (fmt_header.format_version != DSF_FORMAT_VERSION)
			return FALSE;
		if (fmt_header.format_id != DSF_FMTID_RAW)
			return FALSE;

		switch (fmt_header.channel_type)
		{
		case DSF_CHTYPE_MONO:
		case DSF_CHTYPE_STEREO:
		case DSF_CHTYPE_3CHS:
		case DSF_CHTYPE_QUAD:
		case DSF_CHTYPE_4CHS:
		case DSF_CHTYPE_5CHS:
		case DSF_CHTYPE_5_1CHS:
			break;
		default:
			return FALSE;
		}
		if (fmt_header.bits_per_sample != DSF_BPS_LSB && fmt_header.bits_per_sample != DSF_BPS_MSB)
			return FALSE;
	}
	{
		if (!Read(&data_header, sizeof data_header, &dwBytesRead))
			return FALSE;
		if (dwBytesRead != sizeof data_header)
			return FALSE;
		if (memcmp(&data_header.data, &data, sizeof data_header.data) != 0)
			return FALSE;
	}
	return TRUE;
}

void CDSFFile::Reset()
{
	if (hFile == INVALID_HANDLE_VALUE)
		return;

	Seek(dataOffset, NULL, FILE_BEGIN);
}

#ifndef dop_h
#define dop_h

/* Based on DoP open Standard v1.1 */

#define DOP_FREQ_64FS				(176400)	// (44100*64) / 16
#define DOP_FREQ_128FS				(352800)	// (44100*128) / 16

#define DOP_BITS_PER_FRAME			24			// bits per DoP frame
#define DOP_BYTES_PER_FRAME			(DOP_BITS_PER_FRAME >> 3)
#define DOP_DSD_BITS_PER_FRAME		16			// DSD bits in one DoP frame
#define DOP_DSD_BYTES_PER_FRAME		(DOP_DSD_BITS_PER_FRAME >> 3)

#define DOP_MARKER1					0x05		// (0x05 ^ 0xff) == 0xfa
#define DOP_MARKER2					0xfa

#define DOP_MARKER_ALT_1			0x06
#define DOP_MARKER_ALT_2			0xf9

#endif // !dop_h




void WINAPI kpiInit();
void WINAPI kpiDeinit();

UINT GetMyProfileInt(LPWSTR szSectionName, LPWSTR szKeyName, INT nDefault = 0);

TCHAR g_szIniFileName[MAX_PATH];
HMODULE g_hModule;

#define HTAPS    48             /* number of FIR constants */
#define FIFOSIZE 16             /* must be a power of two */
#define FIFOMASK (FIFOSIZE-1)   /* bit mask for FIFO offsets */
#define CTABLES ((HTAPS+7)/8)   /* number of "8 MACs" lookup tables */

class Downsampler_Precalc
{
private:
	/*
	* The 2nd half (48 coeffs) of a 96-tap symmetric lowpass filter
	*/
	double htaps[HTAPS];

	float ctables[CTABLES][256];
	uint8_t bitreverse[256];

	void precalc(void);

public:
	Downsampler_Precalc()
	{
		htaps[0] =
			0.09950731974056658,
			htaps[1] =
			0.09562845727714668,
			htaps[2] =
			0.08819647126516944,
			htaps[3] =
			0.07782552527068175,
			htaps[4] =
			0.06534876523171299,
			htaps[5] =
			0.05172629311427257,
			htaps[6] =
			0.0379429484910187,
			htaps[7] =
			0.02490921351762261,
			htaps[8] =
			0.0133774746265897,
			htaps[9] =
			0.003883043418804416,
			htaps[10] =
			-0.003284703416210726,
			htaps[11] =
			-0.008080250212687497,
			htaps[12] =
			-0.01067241812471033,
			htaps[13] =
			-0.01139427235000863,
			htaps[14] =
			-0.0106813877974587,
			htaps[15] =
			-0.009007905078766049,
			htaps[16] =
			-0.006828859761015335,
			htaps[17] =
			-0.004535184322001496,
			htaps[18] =
			-0.002425035959059578,
			htaps[19] =
			-0.0006922187080790708,
			htaps[20] =
			0.0005700762133516592,
			htaps[21] =
			0.001353838005269448,
			htaps[22] =
			0.001713709169690937,
			htaps[23] =
			0.001742046839472948,
			htaps[24] =
			0.001545601648013235,
			htaps[25] =
			0.001226696225277855,
			htaps[26] =
			0.0008704322683580222,
			htaps[27] =
			0.0005381636200535649,
			htaps[28] =
			0.000266446345425276,
			htaps[29] =
			7.002968738383528e-05,
			htaps[30] =
			-5.279407053811266e-05,
			htaps[31] =
			-0.0001140625650874684,
			htaps[32] =
			-0.0001304796361231895,
			htaps[33] =
			-0.0001189970287491285,
			htaps[34] =
			-9.396247155265073e-05,
			htaps[35] =
			-6.577634378272832e-05,
			htaps[36] =
			-4.07492895872535e-05,
			htaps[37] =
			-2.17407957554587e-05,
			htaps[38] =
			-9.163058931391722e-06,
			htaps[39] =
			-2.017460145032201e-06,
			htaps[40] =
			1.249721855219005e-06,
			htaps[41] =
			2.166655190537392e-06,
			htaps[42] =
			1.930520892991082e-06,
			htaps[43] =
			1.319400334374195e-06,
			htaps[44] =
			7.410039764949091e-07,
			htaps[45] =
			3.423230509967409e-07,
			htaps[46] =
			1.244182214744588e-07,
			htaps[47] =
			3.130441005359396e-08;

		precalc();
	}
	Downsampler_Precalc(const Downsampler_Precalc& other)
	{
		memcpy(ctables, other.ctables, sizeof ctables);
		memcpy(bitreverse, other.bitreverse, sizeof bitreverse);
	}
	Downsampler_Precalc& operator=(const Downsampler_Precalc& other)
	{
		if (this == &other)
			return *this;
		memcpy(ctables, other.ctables, sizeof ctables);
		memcpy(bitreverse, other.bitreverse, sizeof bitreverse);
		return *this;
	}

	float* CTables(int i) {
		return ctables[i];
	}
	float CTables(int x, int y) const {
		return ctables[x][y];
	}

	uint8_t* BitReverse() {
		return bitreverse;
	}
	uint8_t BitReverse(uint8_t i) const {
		return bitreverse[i];
	}
};


class Downsampler
{
private:
	uint8_t fifo[FIFOSIZE];
	unsigned fifopos;

	Downsampler_Precalc& pc;

public:
	Downsampler(Downsampler_Precalc& preCalc) : pc(preCalc)
	{
		reset();
	}
	Downsampler(const Downsampler& other) : pc(other.pc)
	{
		memcpy(fifo, other.fifo, sizeof fifo);
		fifopos = other.fifopos;
	}

	Downsampler& operator= (const Downsampler& other)
	{
		if (this == &other)
			return *this;
		pc = other.pc;
		memcpy(fifo, other.fifo, sizeof fifo);
		fifopos = other.fifopos;
	}

	void reset()
	{
		int i;

		for (i = 0; i < FIFOSIZE; ++i)
			fifo[i] = 0x69; /* my favorite silence pattern */
		fifopos = 0;

		/* 0x69 = 01101001
		* This pattern "on repeat" makes a low energy 352.8 kHz tone
		* and a high energy 1.0584 MHz tone which should be filtered
		* out completely by any playback system --> silence
		*/
	}

	long Downsampler::translate(
		size_t samples,
		const uint8_t* src, ptrdiff_t src_stride,
		int lsbf,
		float *dst, ptrdiff_t dst_stride);

};

void Downsampler_Precalc::precalc(void)
{
	int t, e, m, k;
	double acc;

	for (t = 0, e = 0; t < 256; ++t) {
		bitreverse[t] = e;
		for (m = 128; m && !((e ^= m) & m); m >>= 1)
			;
	}
	for (t = 0; t < CTABLES; ++t) {
		k = HTAPS - t * 8;
		if (k > 8) k = 8;
		for (e = 0; e < 256; ++e) {
			acc = 0.0;
			for (m = 0; m < k; ++m) {
				acc += (((e >> (7 - m)) & 1) * 2 - 1) * htaps[t * 8 + m];
			}
			ctables[CTABLES - 1 - t][e] = (float)acc;
		}
	}
}

long Downsampler::translate(
	size_t samples,
	const uint8_t* src, ptrdiff_t src_stride,
	int lsbf,
	float *dst, ptrdiff_t dst_stride)
{
	unsigned ffp;
	unsigned i;
	unsigned bite1, bite2;
	uint8_t* p;
	double acc;
	long xlated = 0;

	ffp = fifopos;
	lsbf = lsbf ? 1 : 0;
	while (samples-- > 0) {
		bite1 = *src & 0xFFu;
		fifo[ffp] = lsbf ? pc.BitReverse(bite1) : bite1; src += src_stride;

		p = fifo + ((ffp - CTABLES) & FIFOMASK);
		*p = pc.BitReverse(*p & 0xFF);
		acc = 0;
		for (i = 0; i < CTABLES; ++i) {
			bite1 = fifo[(ffp - i) & FIFOMASK] & 0xFF;
			bite2 = fifo[(ffp - (CTABLES * 2 - 1) + i) & FIFOMASK] & 0xFF;
			acc += pc.CTables(i, bite1) + pc.CTables(i, bite2);
		}
		*dst = (float)acc; dst += dst_stride;
		xlated++;
		ffp = (ffp + 1) & FIFOMASK;
	}
	fifopos = ffp;

	return xlated;
}

class Noiseshaper
{
private:
	int sos_count;      /* number of second order sections */
	std::vector<float> t1, t2; /* filter state, owned by ns library */

	float my_ns_coeffs[8];
	//     b1           b2           a1           a2

public:
	Noiseshaper() : sos_count(sizeof(my_ns_coeffs) / sizeof(my_ns_coeffs[0]) * 4), t1(sos_count, 0.0f), t2(sos_count, 0.0f)
	{
		my_ns_coeffs[0] = -1.62666423f,
			my_ns_coeffs[1] = 0.79410094f,
			my_ns_coeffs[2] = 0.61367127f,
			my_ns_coeffs[3] = 0.23311013f,  // section 1
			my_ns_coeffs[4] = -1.44870017f,
			my_ns_coeffs[5] = 0.54196219f,
			my_ns_coeffs[6] = 0.03373857f,
			my_ns_coeffs[7] = 0.70316556f;   // section 2
	}
	Noiseshaper(const Noiseshaper& other)
	{
		sos_count = other.sos_count;
		t1.assign(other.t1.begin(), other.t1.end());
		t2.assign(other.t2.begin(), other.t2.end());
	}

	Noiseshaper& operator=(const Noiseshaper& other)
	{
		if (this == &other)
			return *this;
		t1.assign(other.t1.begin(), other.t1.end());
		t2.assign(other.t2.begin(), other.t2.end());
	}

	~Noiseshaper()
	{
	}

	void reset()
	{
		for (int i = 0; i < sos_count; ++i) {
			t1[i] = t2[i] = 0.0f;
		}
	}

	float get()
	{
		float acc = 0.0;
		const float* c = my_ns_coeffs;
		for (int i = 0; i < sos_count; ++i) {
			float t1i = t1[i];
			float t2i = t2[i];
			t2[i] = (acc -= t1i * c[2] + t2i * c[3]);
			acc += t1i * c[0] + t2i * c[1];
			c += 4;
		}
		return acc;
	}

	void update(float qerror)
	{
		for (int i = 0; i < sos_count; ++i) {
			t2[i] += qerror;
		}
		std::swap(t1, t2);
	}
};

#include <vector>
#include "soxr.h"

class DSD2PCM
{
private:
	long dsd_samples_per_sec;
	long desired_sample_rate;
	int channels;
	int wordSize;
	bool flush_phase;

	Downsampler_Precalc	ds_pc;
	std::vector<Downsampler> ds;
	std::vector<Noiseshaper> ns;

	std::vector<float> buffer;
	size_t buffer_stored = 0;

	soxr_t soxr;

public:
	DSD2PCM() : ds_pc(), soxr(NULL), flush_phase(false)
	{
		Close();
	}

	~DSD2PCM()
	{
		Close();
	}

	void Reset();
	void Open(long DSDsamplesPerSec, int desiredSampleRate, int ch, int desiredWordSize);
	void Close();

	// return: # of samples written
	size_t writeFinal(std::vector<float> resample_data, size_t odone, uint8_t* out);

	// convert channels, src is interlaced as LRLRLR...
	// return: # of samples rendered
	size_t Render(uint8_t* src, size_t src_size, size_t block_size, int lsbf, uint8_t* dst, size_t samplesToRender);

	bool isInFlush() const {
		return flush_phase;
	}

	size_t RenderLast();
	size_t RenderFlush(uint8_t* dst, size_t samplesToRender);
};

namespace {
	long myround(float x)
	{
		return static_cast<long>(x + (x >= 0 ? 0.5f : -0.5f));
	}

	template<typename T>
	struct id { typedef T type; };

	template<typename T>
	T clip(
		T min,
		T v,
		T max)
	{
		if (v<min) return min;
		if (v>max) return max;
		return v;
	}

	void write_intel16(uint8_t* ptr, int16_t word)
	{
		ptr[0] = word & 0xFF;
		ptr[1] = (word >> 8) & 0xFF;
	}

	void write_intel24(uint8_t* ptr, int32_t word)
	{
		ptr[0] = word & 0xFF;
		ptr[1] = (word >> 8) & 0xFF;
		ptr[2] = (word >> 16) & 0xFF;
	}

	void write_intel32(uint8_t* ptr, int32_t word)
	{
		ptr[0] = word & 0xFF;
		ptr[1] = (word >> 8) & 0xFF;
		ptr[2] = (word >> 16) & 0xFF;
		ptr[3] = (word >> 24) & 0xFF;
	}
}

void DSD2PCM::Reset()
{
	buffer.clear();
	buffer_stored = 0;

	for (int ch = 0; ch < channels; ++ch) {
		ds[ch].reset();
		ns[ch].reset();
	}
	flush_phase = false;

	soxr_clear(soxr);
}

void DSD2PCM::Open(long DSDsamplesPerSec, int desiredSampleRate, int ch, int desiredWordSize)
{
	dsd_samples_per_sec = DSDsamplesPerSec;
	channels = ch;
	wordSize = desiredWordSize;
	desired_sample_rate = desiredSampleRate;

	ds.clear();
	ns.clear();
	buffer.clear();
	buffer_stored = 0;
	flush_phase = false;

	for (int i = 0; i < ch; ++i) {
		ds.push_back(Downsampler(ds_pc));
		ns.push_back(Noiseshaper());
	}
	if (soxr != NULL) {
		soxr_delete(soxr);
	}
	{
		soxr_error_t e = NULL;
		soxr_runtime_spec_t spec = soxr_runtime_spec(0);
		soxr = soxr_create(DSDsamplesPerSec / 8, desiredSampleRate, ch, &e, NULL, NULL, &spec);
		if (e != NULL) {
			OutputDebugStringA((char*)e);
			DebugBreak();
		}

	}
}

void DSD2PCM::Close()
{
	dsd_samples_per_sec = channels = 0;
	std::vector<Downsampler> vec;
	std::vector<Noiseshaper> vec1;
	std::vector<float> buffer1;
	ds.swap(vec);
	ns.swap(vec1);
	buffer.swap(buffer1);
	ds.clear();
	ns.clear();
	buffer.clear();
	buffer_stored = 0;

	if (soxr != NULL) {
		soxr_delete(soxr);
		soxr = NULL;
	}
}

// return: # of samples written
size_t DSD2PCM::writeFinal(std::vector<float> resample_data, size_t odone, uint8_t* out)
{
	uint8_t* op = out;

	switch (wordSize) {
	case 16:
		for (int s = 0; s < odone * channels; ) {
			for (int ch = 0; ch < channels; ++ch) {
				float r = resample_data[s] * 32768.0f + ns[ch].get();
				long smp = clip<long>(-32768, myround(r), 32767);
				ns[ch].update(clip<long>(-1, smp - r, 1));
				write_intel16(op, smp);
				op += 2;
				++s;
			}
		}
		break;
	case 24:
		for (int s = 0; s < odone * channels; ) {
			for (int ch = 0; ch < channels; ++ch) {
				float r = resample_data[s] * 8388608.0f;
				long smp = clip<long>(-8388608, myround(r), 8388607);
				write_intel24(op, smp);
				op += 3;
				++s;
			}
		}
		break;
	case 32:
		for (int s = 0; s < odone * channels; ) {
			for (int ch = 0; ch < channels; ++ch) {
				float r = resample_data[s] * (1 << 31);
				long smp = clip<long>(INT32_MIN, myround(r), INT32_MAX);
				write_intel32(op, smp);
				op += 4;
				++s;
			}
		}
		break;
	}
	return odone;
}

// convert channels, src is interlaced as LRLRLR...
// return: # of samples rendered
size_t DSD2PCM::Render(uint8_t* src, size_t src_size, size_t block_size, int lsbf, uint8_t* dst, size_t samplesToRender)
{
	std::vector<float> float_data(src_size, 0), resample_data(src_size, 0);
	size_t idone = 0, odone = 0;

	if (flush_phase) {
		return 0; // RenderFlush(dst, samplesToRender);
	}

	for (int ch = 0; ch < channels; ++ch) {
		ds[ch].translate(src_size / channels, src + ch * block_size, (block_size > 1) ? 1 : channels, lsbf, float_data.data() + ch, channels);
	}

	soxr_process(soxr, float_data.data(), src_size / channels, &idone, resample_data.data(), src_size / channels, &odone);
	if (odone > 0) {
		buffer.insert(buffer.end(), resample_data.begin(), resample_data.begin() + odone * channels);
		buffer_stored += odone;
	}
	if (buffer_stored >= samplesToRender) {
		size_t samplesWritten = writeFinal(buffer, samplesToRender, dst);
		if (samplesWritten > 0) {
			buffer.erase(buffer.begin(), buffer.begin() + samplesToRender * channels);
			buffer_stored -= samplesWritten;

			return samplesWritten;
		}
	}
	return 0;
}

size_t DSD2PCM::RenderLast()
{
	const int src_size = 4096;
	std::vector<float> resample_data(src_size, 0);

	if (flush_phase)
		return buffer_stored;

	size_t idone = 0, odone = 0;
	do {
		soxr_process(soxr, NULL, 0, &idone, resample_data.data(), src_size / channels, &odone);
		if (odone > 0) {
			buffer.insert(buffer.end(), resample_data.begin(), resample_data.begin() + odone * channels);
			buffer_stored += odone;
		}
	} while (odone > 0);

	flush_phase = true;

	return buffer_stored;
}

size_t DSD2PCM::RenderFlush(uint8_t* dst, size_t samplesToRender)
{
	if (buffer_stored == 0) {
		return 0;
	}
	if (buffer_stored < samplesToRender) {
		samplesToRender = buffer_stored;
	}

	size_t samplesWritten = writeFinal(buffer, samplesToRender, dst);
	if (samplesWritten > 0) {
		buffer.erase(buffer.begin(), buffer.begin() + samplesToRender * channels);
		buffer_stored -= samplesWritten;
	}
	return samplesWritten;
}




#include <stack>

struct ChunkStep
{
	uint64_t headerOffset;
	DFFChunkHeader header;
	uint64_t dataOffset;
	uint64_t dataEndOffset;
};

class CDFFFile : public CLargeFile
{
private:
	FRM8Chunk	frm8;
	std::stack<ChunkStep> stack;

	bool readChunkHeader(DFFChunkHeader& header, ChunkStep& step);
	void assignBuffer(uint32_t bytesToRead, std::string& target);

	bool readFRM8(ChunkStep& step, DFFChunkHeader& hdr);
	bool readPROP(ChunkStep& step, DFFChunkHeader& hdr);
	bool readDIIN(ChunkStep& step, DFFChunkHeader& hdr);
public:
	CDFFFile();
	~CDFFFile();

	FRM8Chunk& FRM8() { return frm8; }

	void Reset() { Seek(frm8.dsd.OffsetToData(), NULL, FILE_BEGIN); }
	BOOL Open(LPCWSTR cszFileName);
	void Close();
};

class CWSDFile : public CLargeFile
{
private:
	WSD_GENERAL_INFO	header;
	WSD_DATA_SPEC		data_spec;
	WSD_TEXT			text;

	BOOL checkHeader();

public:
	CWSDFile();
	~CWSDFile();

	BOOL Open(LPCWSTR szFileName);
	void Close();

	void Reset();

	WSD_GENERAL_INFO* Header() { return &header; }
	WSD_DATA_SPEC* DataSpec() { return &data_spec; }
	WSD_TEXT* Text() { return &text; }
};

CDFFFile::CDFFFile()
{

}

CDFFFile::~CDFFFile()
{
	CLargeFile::~CLargeFile();
}

void CDFFFile::Close()
{
	CLargeFile::Close();
}

bool CDFFFile::readChunkHeader(DFFChunkHeader& header, ChunkStep& step)
{
	DWORD dwBytesRead = 0;
	step.headerOffset = Tell();

	if (!Read(&header, sizeof header, &dwBytesRead) || dwBytesRead != sizeof header)
		return false;
	header.ckID = ntohl(header.ckID);
	header.ckDataSize = ntohll(header.ckDataSize);

	step.header = header;
	step.dataOffset = Tell();
	step.dataEndOffset = step.dataOffset + step.header.ckDataSize + (step.header.ckDataSize & 1);

	return true;
}

BOOL CDFFFile::Open(LPCWSTR cszFileName)
{
	if (!CLargeFile::Open(cszFileName))
		return FALSE;

	ChunkStep step;
	DFFChunkHeader hdr;

	while (readChunkHeader(hdr, step))
	{
		DFFID parentID = stack.empty() ? 0x0000 : stack.top().header.ckID;
		bool handled = false;

		stack.push(step);

		handled = handled || readFRM8(step, hdr);
		handled = handled || readPROP(step, hdr);
		handled = handled || readDIIN(step, hdr);
		if (!handled)
		{
			// default action -- skip that chunk
			Seek(step.dataEndOffset, NULL, FILE_BEGIN);
			stack.pop();
		}

	}

	stack.pop();

	if (!stack.empty())
	{
		// invalid stack state -- hiearchy mismatch
	}

	return TRUE;
}

bool CDFFFile::readFRM8(ChunkStep& step, DFFChunkHeader& hdr)
{
	switch (hdr.ckID)
	{
	case DFFID_FRM8:
	{
		frm8.header = hdr;
		frm8.offsetToData = step.dataOffset;

		Read(&frm8.data, sizeof frm8.data, NULL);
		frm8.setupData();
		// descend to subchunks
		break;
	}
	case DFFID_FVER:
	{
		Read(&frm8.fver.data, sizeof frm8.fver.data, NULL);
		frm8.fver.setupData();
		stack.pop(); // ascend to parent (FRM8) chunk
		break;
	}
	case DFFID_DSD_:
	{
		frm8.dsd.header = hdr;
		frm8.dsd.offsetToData = step.dataOffset;
		Seek(step.dataEndOffset, NULL, FILE_BEGIN);
		stack.pop(); // ascend to parent (FRM8) chunk
		break;
	}
	case DFFID_COMT:
	{
		frm8.comt.header = hdr;
		frm8.comt.offsetToData = step.dataOffset;
		Read(&frm8.comt.data, sizeof frm8.comt.data, NULL);
		frm8.comt.setupData();
		for (uint32_t i = 0; i < frm8.comt.data.numComments; i++)
		{
			Comment comment;

			Read(&comment.data, sizeof comment.data, NULL);
			comment.setupData();
			assignBuffer(comment.data.count, comment.commentText);
			frm8.comt.comments.push_back(comment);
		}
		Seek(step.dataEndOffset, NULL, FILE_BEGIN); // may contain padding byte(s)
		stack.pop(); // ascend to parent (FRM8) chunk
		break;
	}
	case DFFID_DST_:
	case DFFID_DSTI:
	case DFFID_MANF:
	default:
		return false;
	}
	return true;
}

bool CDFFFile::readPROP(ChunkStep& step, DFFChunkHeader& hdr)
{
	switch (hdr.ckID)
	{
	case DFFID_PROP:
	{
		frm8.prop.header = hdr;
		frm8.prop.offsetToData = step.dataOffset;
		Read(&frm8.prop.data, sizeof frm8.prop.data, NULL);
		frm8.prop.setupData();
		// descend to subchunks
		break;
	}
	case DFFID_FS__:
		frm8.prop.fs.header = hdr;
		frm8.prop.fs.offsetToData = step.dataOffset;
		Read(&frm8.prop.fs.data, sizeof frm8.prop.fs.data, NULL);
		frm8.prop.fs.setupData();
		stack.pop();	// ascend to parent (PROP) chunk
		break;
	case DFFID_CHNL:
		frm8.prop.chnl.header = hdr;
		frm8.prop.chnl.offsetToData = step.dataOffset;
		Read(&frm8.prop.chnl.data, sizeof frm8.prop.chnl.data, NULL);
		frm8.prop.chnl.setupData();
		for (int i = 0; i < frm8.prop.chnl.data.numChannels; i++)
		{
			DFFID id;
			Read(&id, sizeof id, NULL);
			id = ntohl(id);
			frm8.prop.chnl.chID.push_back(id);
		}
		stack.pop();	// ascend to parent (PROP) chunk
		break;
	case DFFID_CMPR:
		frm8.prop.cmpr.header = hdr;
		frm8.prop.cmpr.offsetToData = step.dataOffset;
		Read(&frm8.prop.cmpr.data, sizeof frm8.prop.cmpr.data, NULL);
		frm8.prop.cmpr.setupData();

		assignBuffer(frm8.prop.cmpr.data.count, frm8.prop.cmpr.compressionName);
		Seek(step.dataEndOffset, NULL, FILE_BEGIN);

		stack.pop();	// ascend to parent (PROP) chunk
		break;
	case DFFID_ABSS:
		frm8.prop.abss.header = hdr;
		frm8.prop.abss.offsetToData = step.dataOffset;
		Read(&frm8.prop.abss.data, sizeof frm8.prop.abss.data, NULL);
		frm8.prop.abss.setupData();
		stack.pop();	// ascend to parent (PROP) chunk
		break;
	case DFFID_LSCO:
		frm8.prop.lsco.header = hdr;
		frm8.prop.lsco.offsetToData = step.dataOffset;
		Read(&frm8.prop.lsco.data, sizeof frm8.prop.lsco.data, NULL);
		frm8.prop.lsco.setupData();
		stack.pop();	// ascend to parent (PROP) chunk
		break;
	default:
		return false;
	}
	return true;
}

bool CDFFFile::readDIIN(ChunkStep& step, DFFChunkHeader& hdr)
{
	switch (hdr.ckID)
	{
	case DFFID_DIIN:
	{
		frm8.diin.header = hdr;
		frm8.diin.offsetToData = step.dataOffset;
		// descend to subchunks
		break;
	}
	case DFFID_DIAR:
	{
		frm8.diin.diar.header = hdr;
		frm8.diin.diar.offsetToData = step.dataOffset;
		Read(&frm8.diin.diar.data, sizeof frm8.diin.diar.data, NULL);
		frm8.diin.diar.setupData();

		assignBuffer(frm8.diin.diar.data.count, frm8.diin.diar.artistText);
		Seek(step.dataEndOffset, NULL, FILE_BEGIN); // may contain padding byte

		stack.pop(); // ascend to parent (DIIN) chunk
		break;
	}
	case DFFID_DITI:
	{
		frm8.diin.diti.header = hdr;
		frm8.diin.diti.offsetToData = step.dataOffset;
		Read(&frm8.diin.diti.data, sizeof frm8.diin.diti.data, NULL);
		frm8.diin.diti.setupData();

		assignBuffer(frm8.diin.diti.data.count, frm8.diin.diti.titleText);
		Seek(step.dataEndOffset, NULL, FILE_BEGIN); // may contain padding byte

		stack.pop(); // ascend to parent (DIIN) chunk
		break;
	}
	default:
		return false;
	}
	return true;
}

CWSDFile::CWSDFile() : CLargeFile()
{

}

CWSDFile::~CWSDFile()
{
	CLargeFile::~CLargeFile();
}

void CWSDFile::Close()
{
	CLargeFile::Close();
}

BOOL CWSDFile::Open(LPCWSTR szFileName)
{
	if (!CLargeFile::Open(szFileName))
		return FALSE;

	if (!checkHeader())
	{
		Close();
		return FALSE;
	}

	Reset();

	return TRUE;
}

void CWSDFile::Reset()
{
	if (hFile == INVALID_HANDLE_VALUE)
		return;

	Seek(header.dataOffset, NULL, FILE_BEGIN);
}

BOOL CWSDFile::checkHeader()
{
	DWORD dwBytesRead = 0;

	if (Read(&header, sizeof header, &dwBytesRead) == FALSE)
		return FALSE;
	if (dwBytesRead != sizeof header)
		return FALSE;
	if (memcmp(header.fileID, WSD_FILEID, 4) != 0)
		return FALSE;

	header.fileSize = ntohllX(header.fileSize);
	header.textOffset = ntohl(header.textOffset);
	header.dataOffset = ntohl(header.dataOffset);

	if (header.textOffset > liFileSize.QuadPart
		|| header.textOffset < sizeof header + sizeof data_spec)
		return FALSE;
	if (header.dataOffset >= liFileSize.QuadPart)
		return FALSE;

	if (Read(&data_spec, sizeof data_spec, &dwBytesRead) == FALSE)
		return FALSE;
	if (dwBytesRead != sizeof data_spec)
		return FALSE;

	data_spec.playbackTime = ntohl(data_spec.playbackTime);
	data_spec.samplingFrequency = ntohl(data_spec.samplingFrequency);
	data_spec.channelAssignment = ntohl(data_spec.channelAssignment);
	data_spec.emphasis = ntohl(data_spec.emphasis);
	data_spec.timeReferenceHi = ntohll(data_spec.timeReferenceLo);	// typoではない
	data_spec.timeReferenceLo = ntohll(data_spec.timeReferenceHi);	// typoではない

	if (header.textOffset != 0)
	{
		Seek(header.textOffset, NULL, FILE_BEGIN);

		if (Read(&text, sizeof text, &dwBytesRead) == FALSE)
			return FALSE;
		if (dwBytesRead != sizeof text)
			return FALSE;
	}
	else
		::ZeroMemory(&text, sizeof text);

	return TRUE;
}

void CDFFFile::assignBuffer(uint32_t bytesToRead, std::string& target)
{
	uint8_t* buf = new uint8_t[bytesToRead + 1];
	buf[bytesToRead] = '\0';
	Read(buf, bytesToRead, NULL);
	target.assign((const char*)buf);
	delete[] buf;
}


#define SAMPLES_PER_BLOCK		(4096)

class CDFFDecoderKpi : public CAbstractKpi
{
private:
	CDFFFile file;
	SOUNDINFO soundinfo;

	BYTE last_marker;
	DSD2PCM dsd2pcm;
	PBYTE srcBuffer;
	DWORD srcBufferSize;
public:

	CDFFDecoderKpi();
	virtual ~CDFFDecoderKpi();

	BOOL Open(LPWSTR szFileName, SOUNDINFO* pInfo, ULONGLONG& dwTagSize);
	void Close();
	DWORD SetPosition(DWORD dwPosition);
	DWORD Render(BYTE* buffer, DWORD dwSize);
	void Reset();


};

class CWSDDecoderKpi : public CAbstractKpi
{
private:
	CWSDFile file;

	BYTE* srcBuffer;
	DWORD srcBufferSize;
	DSD2PCM dsd2pcm;
	SOUNDINFO soundinfo;
	BYTE last_marker;

public:
	CWSDDecoderKpi();
	virtual ~CWSDDecoderKpi();

	BOOL Open(LPWSTR szFileName, SOUNDINFO* pInfo, ULONGLONG& dwTagSize);
	void Close();
	DWORD SetPosition(DWORD dwPosition);
	DWORD Render(BYTE* buffer, DWORD dwSize);
	void Reset();

};


class CDSFDecoderKpi : public CAbstractKpi
{
private:
	CDSFFile file;

	BYTE* srcBuffer;
	DWORD srcBufferSize;

	uint64_t samplesRendered;

	SOUNDINFO soundinfo;
	BYTE last_marker;
	DSD2PCM dsd2pcm;

public:
	CDSFDecoderKpi();
	virtual ~CDSFDecoderKpi();

	BOOL Open(LPWSTR szFileName, SOUNDINFO* pInfo, ULONGLONG& dwTagSize);
	void Close();
	DWORD SetPosition(DWORD dwPosition);
	DWORD Render(BYTE* buffer, DWORD dwSize);
	void Reset();

};

#define SAMPLES_PER_BLOCK		(4096)


CDSFDecoderKpi::CDSFDecoderKpi() : file(), srcBuffer(NULL)
{
}

CDSFDecoderKpi::~CDSFDecoderKpi()
{
	Close();
}

void CDSFDecoderKpi::Close()
{
	dsd2pcm.Close();
	file.Close();
	if (srcBuffer != NULL)
	{
		delete[] srcBuffer;
		srcBuffer = NULL;
	}
}

BOOL CDSFDecoderKpi::Open(LPWSTR szFileName, SOUNDINFO* pInfo, ULONGLONG& dwTagSize)
{
	if (!file.Open(szFileName))
		return FALSE;
	file.Seek(file.Header()->id3v2_pointer, NULL, FILE_BEGIN);
	dwTagSize = file.Header()->id3v2_pointer;
	file.Close();
	if (!file.Open(szFileName))
		return FALSE;
	uint32_t dsd_fs = file.FmtHeader()->sampling_frequency;
	uint32_t channels = file.FmtHeader()->channel_num;
	soundinfo.dwChannels = channels;

	switch (dsd_fs) {
	case DSD_FREQ_64FS:
		soundinfo.dwSamplesPerSec = pInfo->dwSamplesPerSec;
		break;
	case DSD_FREQ_128FS:
		soundinfo.dwSamplesPerSec = pInfo->dwSamplesPerSec;
		break;
	default:
		soundinfo.dwSamplesPerSec = pInfo->dwSamplesPerSec;
	}
	soundinfo.dwReserved1 = soundinfo.dwReserved2 = 0;
	soundinfo.dwSeekable = 1;
	switch (pInfo->dwBitsPerSample)
	{

	case 16:
		soundinfo.dwBitsPerSample = 16;
		soundinfo.dwUnitRender = file.FmtHeader()->block_size_per_channel * channels * 1.5;	// FIXME: 本当？ 
		break;
	case 0:
	case 24:
	default:
		soundinfo.dwBitsPerSample = 24;
		soundinfo.dwUnitRender = file.FmtHeader()->block_size_per_channel * channels * 1.5;	// FIXME: 本当？ 
		break;
	case 32:
		soundinfo.dwBitsPerSample = 32;
		soundinfo.dwUnitRender = file.FmtHeader()->block_size_per_channel * channels * 2;
		break;
	}
	dsd2pcm.Open(dsd_fs, pInfo->dwSamplesPerSec, channels, soundinfo.dwBitsPerSample);
	uint64_t qwSamples = file.FmtHeader()->sample_count;
	qwSamples *= 1000;
	qwSamples /= dsd_fs;
	soundinfo.dwLength = (DWORD)qwSamples;

	memcpy(pInfo, &soundinfo, sizeof soundinfo);
	//pInfo->dwSamplesPerSec /= 16;
	srcBufferSize = file.FmtHeader()->block_size_per_channel * channels;
	srcBuffer = new BYTE[srcBufferSize];
	Reset();

	return TRUE;

fail_cleanup:
	Close();
	return FALSE;
}

void CDSFDecoderKpi::Reset()
{
	file.Reset();
	dsd2pcm.Reset();
	last_marker = DOP_MARKER1;
	samplesRendered = 0;
}

DWORD CDSFDecoderKpi::SetPosition(DWORD dwPos)
{
	if (file.File() == INVALID_HANDLE_VALUE)
		return 0;

	uint64_t bytePos = dwPos;
	bytePos *= file.FmtHeader()->sampling_frequency;
	bytePos /= 1000;
	bytePos >>= 3;

	uint64_t blockPos = bytePos / file.FmtHeader()->block_size_per_channel;

	BYTE marker = last_marker;

	Reset();
	file.Seek(blockPos * file.FmtHeader()->block_size_per_channel * file.FmtHeader()->channel_num, NULL, FILE_CURRENT);
	samplesRendered = file.FmtHeader()->block_size_per_channel * 8 * blockPos;

	uint64_t newPos = blockPos;
	newPos *= file.FmtHeader()->block_size_per_channel;
	newPos <<= 3;
	newPos *= 1000;
	newPos /= file.FmtHeader()->sampling_frequency;

	last_marker = marker;

	return (DWORD)newPos;
}

DWORD CDSFDecoderKpi::Render(BYTE* buffer, DWORD dwSizeSample)
{
	DWORD dwBytesRead = 0;
	DWORD dwSize = dwSizeSample * (soundinfo.dwChannels * (soundinfo.dwBitsPerSample / 8));
	PBYTE d = buffer;
	uint64_t sampleCount = file.FmtHeader()->sample_count;
	DWORD dwBytesPerBlockChannel = file.FmtHeader()->block_size_per_channel;
	int bps = file.FmtHeader()->bits_per_sample;
	uint64_t dataEndPos = file.DataOffset() + file.DataHeader()->size - 12;
	DWORD totalSamplesWritten = 0, samplesWritten = 0;
	DWORD dwSamplesToRender = dwSizeSample;

	::ZeroMemory(buffer, dwSize);
	while (dwSamplesToRender > 0 && samplesRendered < sampleCount)
	{
		if (!dsd2pcm.isInFlush() && file.Tell() >= dataEndPos) {
			dsd2pcm.RenderLast();
		}

		if (!dsd2pcm.isInFlush()) {
			file.Read(srcBuffer, dwBytesPerBlockChannel * soundinfo.dwChannels, &dwBytesRead);
			if (dwBytesRead < dwBytesPerBlockChannel * soundinfo.dwChannels) {
				dsd2pcm.RenderLast();
			}
		}
    	samplesWritten = dsd2pcm.Render(srcBuffer, dwBytesRead, dwBytesPerBlockChannel, bps == DSF_BPS_LSB ? 1 : 0, d, dwSamplesToRender);
		d += samplesWritten * soundinfo.dwChannels * (soundinfo.dwBitsPerSample / 8);
		totalSamplesWritten += samplesWritten;
		if (dsd2pcm.isInFlush() && samplesWritten < dwSamplesToRender)
			break;
		dwSamplesToRender -= samplesWritten;
		//samplesRendered += samplesWritten * 16;

		//if (!dsd2pcm.isInFlush() && dwSamplesToRender * 16 > sampleCount - samplesRendered) {
		//	dsd2pcm.RenderLast();
		//}
	}

	return totalSamplesWritten;
}


CDFFDecoderKpi::CDFFDecoderKpi() : file(), srcBuffer(NULL)
{
}

CDFFDecoderKpi::~CDFFDecoderKpi()
{
	Close();
}

void CDFFDecoderKpi::Close()
{
	dsd2pcm.Close();
	file.Close();
	if (srcBuffer != NULL)
	{
		delete[] srcBuffer;
		srcBuffer = NULL;
	}
}

void CDFFDecoderKpi::Reset()
{
	file.Reset();
	dsd2pcm.Reset();
	last_marker = DOP_MARKER1;
}
CString dsdart, dsdtitle;
BOOL CDFFDecoderKpi::Open(LPWSTR szFileName, SOUNDINFO* pInfo, ULONGLONG& dwTagSize)
{
	if (!file.Open(szFileName))
		return FALSE;

	// DST compression is not supported
	if (file.FRM8().prop.cmpr.compressionName != CMPR_NAME_DSD)
		return FALSE;

	uint32_t dsd_fs = file.FRM8().prop.fs.data.sampleRate;
	uint32_t channels = file.FRM8().prop.chnl.data.numChannels;

	soundinfo.dwChannels = channels;

	switch (dsd_fs) {
	case DSD_FREQ_64FS:
		soundinfo.dwSamplesPerSec = pInfo->dwSamplesPerSec;
		break;
	case DSD_FREQ_128FS:
		soundinfo.dwSamplesPerSec = pInfo->dwSamplesPerSec;
		break;
	default:
		// 256FS とかはこっちを通す
		if (dsd_fs % 44100 == 0)
			soundinfo.dwSamplesPerSec = pInfo->dwSamplesPerSec;
		else
			goto fail_cleanup;
	}
	soundinfo.dwReserved1 = soundinfo.dwReserved2 = 0;
	soundinfo.dwSeekable = 1;


	switch (pInfo->dwBitsPerSample)
	{
	case 0:
	case 24:
		soundinfo.dwBitsPerSample = 24;
		soundinfo.dwUnitRender = 3 * channels * SAMPLES_PER_BLOCK / 2;
		break;
	case 32:
	default:
		soundinfo.dwBitsPerSample = 32;
		soundinfo.dwUnitRender = 4 * channels * SAMPLES_PER_BLOCK / 2;
		break;
	}
	dsd2pcm.Open(dsd_fs, soundinfo.dwSamplesPerSec, channels, soundinfo.dwBitsPerSample);
	{
		uint64_t samples = file.FRM8().dsd.DataSize();
		dwTagSize = samples;
		samples <<= 3;
		samples *= 1000;
		samples /= dsd_fs;
		samples /= channels;

		soundinfo.dwLength = (DWORD)samples;
	}

	memcpy(pInfo, &soundinfo, sizeof soundinfo);

	srcBufferSize = SAMPLES_PER_BLOCK * channels;
	srcBuffer = new BYTE[srcBufferSize];

	Reset();

	return TRUE;

fail_cleanup:
	Close();
	return FALSE;
}

DWORD CDFFDecoderKpi::SetPosition(DWORD dwPos)
{
	if (file.File() == INVALID_HANDLE_VALUE)
		return 0;

	uint64_t bytePos = dwPos;
	bytePos *= file.FRM8().prop.fs.data.sampleRate;
	bytePos *= file.FRM8().prop.chnl.data.numChannels;
	bytePos /= 1000;
	bytePos >>= 3;

	BYTE marker = last_marker;

	Reset();
	file.Seek(bytePos, NULL, FILE_CURRENT);

	last_marker = marker;

	// bytePos から求めたミリ秒位置は、モノラル 64FS においても dwPos と 1ms 未満の誤差でしか無い
	return dwPos;
}

DWORD CDFFDecoderKpi::Render(BYTE* buffer, DWORD dwSizeSample)
{
	DWORD dwBytesRead = 0;
	DWORD dwSize = dwSizeSample * (soundinfo.dwChannels * (soundinfo.dwBitsPerSample / 8));
	PBYTE d = buffer;
	uint64_t dsdEndPos = file.FRM8().dsd.OffsetToData() + file.FRM8().dsd.DataSize();
	DWORD totalSamplesWritten = 0, samplesWritten = 0;
	DWORD dwSamplesToRender = dwSizeSample;

	::ZeroMemory(buffer, dwSize);
	while (dwSamplesToRender > 0) {
		DWORD dwBytesToRead = srcBufferSize;

		if (!dsd2pcm.isInFlush() && file.Tell() >= dsdEndPos) {
			dsd2pcm.RenderLast();
		}

		if (dsdEndPos - file.Tell() < dwBytesToRead)
			dwBytesToRead = (DWORD)(dsdEndPos - file.Tell());

		if (!dsd2pcm.isInFlush() && !file.Read(srcBuffer, dwBytesToRead, &dwBytesRead))
			break;

		samplesWritten = dsd2pcm.Render(srcBuffer, dwBytesRead, 1, 0, d, dwSamplesToRender);
		d += samplesWritten * soundinfo.dwChannels * (soundinfo.dwBitsPerSample / 8);
		totalSamplesWritten += samplesWritten;

		if (dsd2pcm.isInFlush() && samplesWritten < dwSamplesToRender)
			break;
		dwSamplesToRender -= samplesWritten;
		//if (dwBytesRead < srcBufferSize)
		//	break;
	}

	return totalSamplesWritten;
}


CWSDDecoderKpi::CWSDDecoderKpi() : file(), srcBuffer(NULL)
{

}

CWSDDecoderKpi::~CWSDDecoderKpi()
{
	Close();
}

void CWSDDecoderKpi::Close()
{
	dsd2pcm.Close();
	file.Close();
	if (srcBuffer != NULL)
	{
		delete[] srcBuffer;
		srcBuffer = NULL;
	}
}

void CWSDDecoderKpi::Reset()
{
	file.Reset();
	dsd2pcm.Reset();
	last_marker = DOP_MARKER1;
}

BOOL CWSDDecoderKpi::Open(LPWSTR szFileName, SOUNDINFO* pInfo, ULONGLONG& dwTagSize)
{
	if (!file.Open(szFileName))
		return FALSE;

	uint32_t dsd_fs = file.DataSpec()->samplingFrequency;
	uint32_t channels = file.DataSpec()->channels;

	soundinfo.dwChannels = channels;

	switch (dsd_fs) {
	case DSD_FREQ_64FS:
		soundinfo.dwSamplesPerSec = pInfo->dwSamplesPerSec;
		break;
	case DSD_FREQ_128FS:
		soundinfo.dwSamplesPerSec = pInfo->dwSamplesPerSec;
		break;
	default:
		// 256FS とかはこっちを通す
		if (dsd_fs % 44100 == 0)
			soundinfo.dwSamplesPerSec = pInfo->dwSamplesPerSec;
		else
			goto fail_cleanup;
	}
	soundinfo.dwReserved1 = soundinfo.dwReserved2 = 0;
	soundinfo.dwSeekable = 1;

	dsd2pcm.Open(dsd_fs, soundinfo.dwSamplesPerSec, channels, soundinfo.dwBitsPerSample);
	switch (pInfo->dwBitsPerSample)
	{
	case 0:
	case 24:
		soundinfo.dwBitsPerSample = 24;
		soundinfo.dwUnitRender = 3 * channels * SAMPLES_PER_BLOCK / 2;
		break;
	case 32:
	default:
		soundinfo.dwBitsPerSample = 32;
		soundinfo.dwUnitRender = 4 * channels * SAMPLES_PER_BLOCK / 2;
		break;
	}

	{
		uint64_t samples = file.FileSize() - file.Header()->dataOffset;

		samples <<= 3;
		samples *= 1000;
		samples /= dsd_fs;
		samples /= channels;

		soundinfo.dwLength = (DWORD)samples;
	}

	memcpy(pInfo, &soundinfo, sizeof soundinfo);

	srcBufferSize = SAMPLES_PER_BLOCK * channels;
	srcBuffer = new BYTE[srcBufferSize];

	Reset();

	return TRUE;

fail_cleanup:
	Close();
	return FALSE;
}

DWORD CWSDDecoderKpi::SetPosition(DWORD dwPos)
{
	if (file.File() == INVALID_HANDLE_VALUE)
		return 0;

	uint64_t bytePos = dwPos;
	bytePos *= file.DataSpec()->samplingFrequency;
	bytePos *= file.DataSpec()->channels;
	bytePos /= 1000;
	bytePos >>= 3;

	BYTE marker = last_marker;

	Reset();
	file.Seek(bytePos, NULL, FILE_CURRENT);

	last_marker = marker;

	// bytePos から求めたミリ秒位置は、モノラル 64FS においても dwPos と 1ms 未満の誤差でしか無い
	return dwPos;
}

DWORD CWSDDecoderKpi::Render(BYTE* buffer, DWORD dwSizeSample)
{
	DWORD dwBytesRead = 0;
	DWORD dwSize = dwSizeSample * (soundinfo.dwChannels * (soundinfo.dwBitsPerSample / 8));
	PBYTE d = buffer;
	DWORD totalSamplesWritten = 0, samplesWritten = 0;
	DWORD dwSamplesToRender = dwSizeSample;

	::ZeroMemory(buffer, dwSize);
	while (dwSamplesToRender > 0)
	{
		if (!dsd2pcm.isInFlush()) {
			file.Read(srcBuffer, srcBufferSize, &dwBytesRead);
			if (dwBytesRead < srcBufferSize) {
				dsd2pcm.RenderLast();
			}
		}

		samplesWritten = dsd2pcm.Render(srcBuffer, dwBytesRead, 1, 0, d, dwSamplesToRender);
		d += samplesWritten * soundinfo.dwChannels * (soundinfo.dwBitsPerSample / 8);
		totalSamplesWritten += samplesWritten;

		if (dsd2pcm.isInFlush() && samplesWritten < dwSamplesToRender)
			break;
		dwSamplesToRender -= samplesWritten;

		//if (dwBytesRead < srcBufferSize)
		//	break;
	}

	return totalSamplesWritten;
}




CAbstractKpi* CreateKpiDecoderInstance(LPCWSTR szFileName);
//BOOL GetDSDTagInfo(LPCWSTR cszFileName, IKmpTagInfo* pInfo);


CAbstractKpi* CreateKpiDecoderInstance(LPCWSTR szFileName)
{
	wchar_t* ext = wcsrchr((wchar_t*)szFileName, L'.');
	CAbstractKpi* kpi = NULL;

	if (ext == NULL)
		return NULL;

	if (_wcsicmp(ext, L".dsf") == 0) {
		kpi = new CDSFDecoderKpi();
	}
	if (_wcsicmp(ext, L".wsd") == 0) {
		kpi = new CWSDDecoderKpi();
	}
	if (_wcsicmp(ext, L".dff") == 0) {
		kpi = new CDFFDecoderKpi();
	}

	return kpi;
}



void WINAPI kpiInit()
{
	TCHAR* pDot;

	GetModuleFileName(::g_hModule, ::g_szIniFileName, MAX_PATH);
	pDot = wcsrchr(g_szIniFileName, '.');
	wcsncpy_s(pDot, MAX_PATH - (pDot - g_szIniFileName), L".ini", 4);
}

void WINAPI kpiDeinit()
{
}
class dsd {
public:

	CAbstractKpi* WINAPI kpiOpen(const TCHAR* cszFileName, SOUNDINFO* pInfo, ULONGLONG& dwTagSize)
	{
		CAbstractKpi* d = CreateKpiDecoderInstance(cszFileName);
		if (d == NULL) return NULL;

		if (d->Open((LPWSTR)cszFileName, pInfo, dwTagSize))
			return (CAbstractKpi*)d;
		delete d;
		return NULL;
	}

	void WINAPI kpiClose(HKMP hKMP)
	{
		if (hKMP) {
			CAbstractKpi* d = (CAbstractKpi*)hKMP;
			d->Close();
			TRY{
				delete d;
			}
				CATCH_ALL(e) {
			}
			END_CATCH_ALL;

			hKMP = NULL;
		}
	}

	DWORD WINAPI kpiRender(HKMP hKMP, BYTE* Buffer, DWORD dwSize)
	{
		if (hKMP) {
			CAbstractKpi* d = (CAbstractKpi*)hKMP;
			TRY{
				return d->Render(Buffer, dwSize);
			}CATCH_ALL(e) {}END_CATCH_ALL;
		}
		return 0;
	}

	DWORD WINAPI kpiSetPosition(HKMP hKMP, DWORD dwPos)
	{
		if (hKMP) {
			CAbstractKpi* d = (CAbstractKpi*)hKMP;
			return d->SetPosition(dwPos);
		}
		return 0;
	}
};

UINT GetMyProfileInt(LPWSTR szSectionName, LPWSTR szKeyName, INT nDefault)
{
	return ::GetPrivateProfileInt(szSectionName, szKeyName, nDefault, ::g_szIniFileName);
}

