/*
 * LoggerMessage.h
 *
 * BSD license follows (http://www.opensource.org/licenses/bsd-license.php)
 * 
 * Copyright (c) 2010 Florent Pillet <fpillet@gmail.com> All Rights Reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * Redistributions of  source code  must retain  the above  copyright notice,
 * this list of  conditions and the following  disclaimer. Redistributions in
 * binary  form must  reproduce  the  above copyright  notice,  this list  of
 * conditions and the following disclaimer  in the documentation and/or other
 * materials  provided with  the distribution.  Neither the  name of  Florent
 * Pillet nor the names of its contributors may be used to endorse or promote
 * products  derived  from  this  software  without  specific  prior  written
 * permission.  THIS  SOFTWARE  IS  PROVIDED BY  THE  COPYRIGHT  HOLDERS  AND
 * CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT
 * NOT LIMITED TO, THE IMPLIED  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A  PARTICULAR PURPOSE  ARE DISCLAIMED.  IN  NO EVENT  SHALL THE  COPYRIGHT
 * HOLDER OR  CONTRIBUTORS BE  LIABLE FOR  ANY DIRECT,  INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY,  OR CONSEQUENTIAL DAMAGES (INCLUDING,  BUT NOT LIMITED
 * TO, PROCUREMENT  OF SUBSTITUTE GOODS  OR SERVICES;  LOSS OF USE,  DATA, OR
 * PROFITS; OR  BUSINESS INTERRUPTION)  HOWEVER CAUSED AND  ON ANY  THEORY OF
 * LIABILITY,  WHETHER  IN CONTRACT,  STRICT  LIABILITY,  OR TORT  (INCLUDING
 * NEGLIGENCE  OR OTHERWISE)  ARISING  IN ANY  WAY  OUT OF  THE  USE OF  THIS
 * SOFTWARE,   EVEN  IF   ADVISED  OF   THE  POSSIBILITY   OF  SUCH   DAMAGE.
 * 
 */
#include <time.h>
#import <Cocoa/Cocoa.h>

@interface LoggerMessage : NSObject <NSCoding, NSCopying>
{
	struct timeval timestamp;	// seconds and microseconds

	NSString *tag;				// non-retained (we use a global pool for domains)
	NSMutableDictionary *parts;	// for non-standard parts transmitted by the clients, store the data in this dictionary
	id message;					// NSString, NSData or image data
	NSImage *image;				// if the message is an image, the image gets decoded once it's being accessed

	NSUInteger sequence;		// message's number if order of reception

	NSString *threadID;

	short level;
	short type;
	short contentsType;			// the type of message data (string, data, image)

	// indentation (blocks) management. Since the contents of log is immutable
	// we can speed up by caching some data
	short indent;				// horizontal indent (count of nested blockstarts)
	int distanceFromParent;		// distance from last blockStart (thisMsgIndex - parentMsgIndex)
	NSSize imageSize;
	NSSize cachedCellSize;		// we use this to cache the cell's height when recomputing if the width didn't change
}

@property (nonatomic, readonly) short contentsType;
@property (nonatomic, readonly) NSDictionary *parts;
@property (nonatomic, readonly) struct timeval timestamp;	// full timestamp (seconds & microseconds)
@property (nonatomic, retain) NSString *tag;
@property (nonatomic, retain) id message;
@property (nonatomic, readonly) short type;
@property (nonatomic, readonly) short level;
@property (nonatomic, assign) short indent;
@property (nonatomic, assign) int distanceFromParent;
@property (nonatomic, readonly) NSString *threadID;
@property (nonatomic, readonly) NSSize imageSize;
@property (nonatomic, assign) NSSize cachedCellSize;
@property (nonatomic, retain) NSImage *image;

- (void)computeTimeDelta:(struct timeval *)td since:(LoggerMessage *)previousMessage;

@end

enum {
	kMessageString = 0,
	kMessageData,
	kMessageImage
};