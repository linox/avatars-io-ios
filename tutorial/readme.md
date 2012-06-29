Avatar Picker Tutorial
======================

Avatar Picker Plus provides an interface for the avatars.io service.  It provides an easy way for your users to select or create an avatar to use with your application or service.  This tutorial shows you how to set up the avatar picker and how the delegate functions work.  It was written using version 5.0 of the iOS SDK and version 4.2 of Xcode.  Uses Chute SDK version 1.0.4 or newer (the version number can be found in the GCConstants.h file).  Some changes may need to be made for other software versions.

![screen1](https://github.com/chute/avatars-io-ios/raw/master/screenshots/ACT_1.PNG)
![screen2](https://github.com/chute/avatars-io-ios/raw/master/screenshots/ACT_2.PNG)
![screen3](https://github.com/chute/avatars-io-ios/raw/master/screenshots/ACT_3.PNG)

Create A New Project
--------------------
Start by creating a new Xcode project.  A single view application will be easiest to modify for this tutorial.  You can choose whatever name you like, I'll call it AvatarPickerTutorial.  Be sure that “Use Automatic Reference Counting” is unchecked as the SDK does not currently support ARC.

![screen4](https://github.com/chute/avatars-io-ios/raw/master/screenshots/ACT_4.PNG)

Preparation
-----------
1.  Download the AvatarPickerPlus component and Chute SDK from https://github.com/chute/avatars-io-ios
2.  Create a Chute developer account and make a new app in Chute at http://apps.getchute.com/
	*  For the URL you can enter http://getchute.com/ if you don't have a site for your app
	*  For the Callback URL you can use http://getchute.com/oauth/callback if you don't need callbacks for another purpose.

![screen5](https://github.com/chute/avatars-io-ios/raw/master/screenshots/ACT_5.PNG)
![screen6](https://github.com/chute/avatars-io-ios/raw/master/screenshots/ACT_6.PNG)

Add The SDK And Component And Link Dependancies
-----------------------------------------------
1. Add the SDK to the project
2. Add the picker component
3. Link the required libraries
     *  AssetsLibrary
     *  CFNetwork
     *  EventKit
     *  libz.dylib
     *  MessageUI
     *  MobileCoreServices
     *  Security
     *  SystemConfiguration

![screen7](https://github.com/chute/avatars-io-ios/raw/master/screenshots/ACT_7.PNG)

Edit Your App ID And Secret
---------------------------
The next step is to enter your chute app information in the GCConstants.h file.  This file can be found at the root of the Chute SDK directory.  You will need to fill in your APP ID and APP secret from the summary tab of your admin panel, you will also need the access token listed in the admin panel later in the tutorial.  If you used a custom Redirect URL when setting up your app on Chute you will also need to adjust the `kOauthCallbackURL` to match the callback url you set.  Then set the `kOauthCallbackRelativeURL` to everything after the base in the callback url.  If you used `http://getchute.com/oauth/callback` then you can leave these as they are.

![screen8](https://github.com/chute/avatars-io-ios/raw/master/screenshots/ACT_8.PNG)

At this point you may want to try running the project to make sure that everything is added ok.  If it builds then everything should be correctly added and linked.

Set APTViewController As Delegate And Add Objects/Methods
-----------------------------------------------
In your APTViewController.h file import AvatarPickerPlus.h and set up the class as a `AvatarPickerPlusDelegate`.  Then add a UIImageView object for the avatar, a label for displaying the URL and a method for showing the picker.  This should look similar to this

viewController.h

```objective-c
	
	#import <UIKit/UIKit.h>
	#import "AvatarPickerPlus.h"
	
	@interface APTViewController : UIViewController <AvatarPickerPlusDelegate>
	
	@property (nonatomic, readonly) IBOutlet UIImageView *avatar;
	@property (nonatomic, readonly) IBOutlet UILabel *urlLabel;
	
	-(IBAction)avatarClicked:(id)sender;
	
```

Synthesize ImageView And Write The Display Method
-------------------------------------------------
In APTViewController.m you now need to synthesize your avatar object, synthesize your urlLabel object and write the method to display the avatar component.  The method will initialize the controller, set itself as the delegate, present it and release it.  The avatar picker also requires a default access token to use for API calls, you can get this from your app dashboard at apps.getchute.com on the same screen you got your appid and secret earlier.  The code for all this is

viewController.m

```objective-c
	
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
	
```

Write The Delegate Methods
--------------------------
The AvatarPickerPlusDelegate methods are `AvatarPickerControllerDidCancel:` and `AvatarPickerController:didFinishPickingMediaWithInfo:`.  These both return a reference to the picker and the media one returns a dictionary with a NSString containing the URL of the avatar and a UIImage of the avatar itself.  So our cancel method will just dismiss the picker and our success method will display the image in the imageView, display the url in the urlLabel and dismiss the picker.  The code for these methods is

viewController.m

```objective-c
	
	-(void)AvatarPickerController:(AvatarPickerPlus *)picker didFinishPickingMediaWithInfo:(NSDictionary *)info{
	    [avatar setImage:[info objectForKey:AvatarPickerImage]];
	    [urlLabel setText:[NSString stringWithFormat:@"%@",[info objectForKey:AvatarPickerURLString]]];
	    [self dismissModalViewControllerAnimated:YES];
	}
	
	-(void)AvatarPickerControllerDidCancel:(AvatarPickerPlus *)picker{
	    [self dismissModalViewControllerAnimated:YES];
	}
	
```

Create The UI
-------------
Open APTViewController.xib and add label and a squre UIImageView.  Hook the UIImageView up to the avatar object.  Add a touch gesture to the UIImageView and set it's selector to the avatarClicked function.  You do this by draging the tap gesture recognizer object over the UIImageView to associate the gesture with that object, then right click the file owner in the left pane and left-click and drag from the circle next to the avatarClicked method to the tap gesture in the list of objects on the left.  Next you want to set the background color of the UIImageView to white and enable user interaction on it so that the tap gesture will work.  These are both done from the attribute inspector tab in the right pane when you have the UIImageView selected.

![screen9](https://github.com/chute/avatars-io-ios/raw/master/screenshots/ACT_9.PNG)

Conclusion
----------
You should have a fully working app now that allows you to either select an existing avatar or set up a new avatar.  With just a few lines of code you can add user avatars to your app that are cross platform and persistent.  More advanced features allow you to set a custom URL ending so that your URL for a user never changes when uploading a new avatar, or to only allow avatar selection from specific services.  Please leave feedback in the github repo if you have any questions, would like to suggest a feature or encounter an issue with the component.