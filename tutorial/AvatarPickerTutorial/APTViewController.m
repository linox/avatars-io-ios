//
//  APTViewController.m
//  AvatarPickerTutorial
//
//  Created by Brandon Coston on 6/26/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "APTViewController.h"

@interface APTViewController ()

@end

@implementation APTViewController
@synthesize avatar;
@synthesize urlLabel;

-(IBAction)avatarClicked:(id)sender{
    AvatarPickerPlus *picker = [[AvatarPickerPlus alloc] init];
    [picker setDelegate:self];
    [picker setDefaultAccessToken:@"PLACE_ACCESS_TOKEN_HERE"];
    [self presentViewController:picker animated:YES completion:^(void){
        [picker release];
    }];
}

-(void)AvatarPickerController:(AvatarPickerPlus *)picker didFinishPickingMediaWithInfo:(NSDictionary *)info{
    [avatar setImage:[info objectForKey:AvatarPickerImage]];
    [urlLabel setText:[NSString stringWithFormat:@"%@",[info objectForKey:AvatarPickerURLString]]];
    [self dismissModalViewControllerAnimated:YES];
}

-(void)AvatarPickerControllerDidCancel:(AvatarPickerPlus *)picker{
    [self dismissModalViewControllerAnimated:YES];
}

- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view, typically from a nib.
}

- (void)viewDidUnload
{
    [super viewDidUnload];
    // Release any retained subviews of the main view.
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    return (interfaceOrientation != UIInterfaceOrientationPortraitUpsideDown);
}

@end
