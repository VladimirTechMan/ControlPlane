//
//  SUStatusController.m
//  Sparkle
//
//  Created by Andy Matuschak on 3/14/06.
//  Copyright 2006 Andy Matuschak. All rights reserved.
//

#import "Sparkle.h"
#import "SUStatusController.h"

@implementation SUStatusController

- (id)initWithHostBundle:(NSBundle *)hb
{
	self = [super initWithHostBundle:hb windowNibName:@"SUStatus"];
	if (self)
	{
		hostBundle = [hb retain];
		[self setShouldCascadeWindows:NO];
	}
	return self;
}

- (void)dealloc
{
	[hostBundle release];
	[title release];
	[statusText release];
	[buttonTitle release];
	[super dealloc];
}

- (void)awakeFromNib
{
	[[self window] center];
	[[self window] setFrameAutosaveName:@"SUStatusFrame"];
	[progressBar setUsesThreadedAnimation:YES];
}

- (NSString *)windowTitle
{
	return [NSString stringWithFormat:SULocalizedString(@"Updating %@", nil), [hostBundle name]];
}

- (NSImage *)applicationIcon
{
	return [hostBundle icon];
}

- (void)beginActionWithTitle:(NSString *)aTitle maxProgressValue:(double)aMaxProgressValue statusText:(NSString *)aStatusText
{
	[self willChangeValueForKey:@"title"];
	title = [aTitle copy];
	[self didChangeValueForKey:@"title"];
	
	[self setMaxProgressValue:aMaxProgressValue];
	[self setStatusText:aStatusText];
}

- (void)setButtonTitle:(NSString *)aButtonTitle target:target action:(SEL)action isDefault:(BOOL)isDefault
{
	[self willChangeValueForKey:@"buttonTitle"];
	buttonTitle = [aButtonTitle copy];
	[self didChangeValueForKey:@"buttonTitle"];	
	
	[self window];
	[actionButton sizeToFit];
	// Except we're going to add 15 px for padding.
	[actionButton setFrameSize:NSMakeSize([actionButton frame].size.width + 15, [actionButton frame].size.height)];
	// Now we have to move it over so that it's always 15px from the side of the window.
	[actionButton setFrameOrigin:NSMakePoint([[self window] frame].size.width - 15 - [actionButton frame].size.width, [actionButton frame].origin.y)];	
	// Redisplay superview to clean up artifacts
	[[actionButton superview] display];
	
	[actionButton setTarget:target];
	[actionButton setAction:action];
	[actionButton setKeyEquivalent:isDefault ? @"\r" : @""];
}

- (void)setButtonEnabled:(BOOL)enabled
{
	[actionButton setEnabled:enabled];
}

- (double)progressValue
{
	return progressValue;
}

- (void)setProgressValue:(double)value
{
	progressValue = value;
}

- (double)maxProgressValue
{
	return maxProgressValue;
}

- (void)setMaxProgressValue:(double)value
{
	maxProgressValue = value;
	[self setProgressValue:0];
	[progressBar setIndeterminate:(value == 0)];
}

- (void)setStatusText:(NSString *)aStatusText
{
	statusText = [aStatusText copy];
}

@end