//
//  APTViewController.h
//  AvatarPickerTutorial
//
//  Created by Brandon Coston on 6/26/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "AvatarPickerPlus.h"

@interface APTViewController : UIViewController <AvatarPickerPlusDelegate>

@property (nonatomic, readonly) IBOutlet UIImageView *avatar;
@property (nonatomic, readonly) IBOutlet UILabel *urlLabel;

-(IBAction)avatarClicked:(id)sender;

@end
