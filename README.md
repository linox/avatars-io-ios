AvatarPickerPlus
==============

no external dependancies beyond Chute SDK (version 1.0.7 or newer)

Description
-----------

This class allows mobile integration of the Avatars.io platform.  It allows a developer to easily integrate user avatars into their app.  Avatars.io takes care of hosting and providing links to avatars for your users.  This component can be dropped into your app to provide an easy means of selecting either a user's avatar from an existing service or uploading a new avatar from a variety of sources.

Screenshots
-----------
![screen1](https://github.com/chute/avatars-io-ios/raw/master/screenshots/APPC_1.PNG)
![screen2](https://github.com/chute/avatars-io-ios/raw/master/screenshots/APPC_2.PNG)
![screen3](https://github.com/chute/avatars-io-ios/raw/master/screenshots/APPC_3.PNG)
![screen4](https://github.com/chute/avatars-io-ios/raw/master/screenshots/APPC_4.PNG)
![screen5](https://github.com/chute/avatars-io-ios/raw/master/screenshots/APPC_5.PNG)

Subclassing
-----------

While subclassing this component is possible, it is not really recommended.  Image selection is passed to a delegate method so any custom behavior can be handled there.

Initialization
--------------

 *   allowedServices (optional) - `AvatarPickerPlusAllowedServices` - You can set which services you want the user to link from.  The available services are Facebook, Twitter, Instagram, Flickr, Picasa, and Gravatar.  The actual values are `APPAllowFacebook`, `APPAllowTwitter`, `APPAllowInstagram`, `APPAllowFlickr`, `APPAllowPicasa`, `APPAllowGravatar`.  You can set multiple services by bitwise ORing them together.  Such as `allowedServices = APPAllowFacebook|APPAllowTwitter;`.  If not set it defaults to all services.
 *   avatarPath (optional) - `NSString` - If you want to set a specific ending path for your avatars (such as your user's ID or name) you can use this to set it.  If not set a unique shortcut will be generated automatically.
 *   useStandardDevicePicker (optional) - `BOOL` - If YES then the picker will use the `UIImagePickerController` to select images from the device rather than the custom picker.  This is for apps that don't want to ask users for location services.  If not set it defaults to NO.
 *   defaultAccessToken (required)- `NSString` - Since the user is not required to log into any services to use this component, this default access token will be used for any upload calls that the component uses when your user isn't logged in.  When you create an app with any chute service you are provided an access token for the app.  This can be used here.
 *   delegate (required) - `UIViewController <AvatarPickerPlusDelegate>` - The delegate for this component.  This is used to pass back the avatar and it's URL if picked or to let the app know if the user canceled.  It should implement two methods.
    *  `-(void)AvatarPickerController:(AvatarPickerPlus *)picker didFinishPickingMediaWithInfo:(NSDictionary *)info;`
    *  `-(void)AvatarPickerControllerDidCancel:(AvatarPickerPlus *)picker;`


Implementation
--------------


```objective-c

	/////////////////////////
	//     Basic Setup     //
	/////////////////////////
	
    -(void)showAvatarPickerPlus{
    	AvatarPickerPlus *picker = [[AvatarPickerPlus alloc] init];
	    [picker setDelegate:self];
	    [picker setDefaultAccessToken:@"YOUR_ACCESS_TOKEN"];
	    [self presentModalViewController:picker animated:YES];
	    [picker release];
	}
	-(void)AvatarPickerController:(AvatarPickerPlus *)picker didFinishPickingMediaWithInfo:(NSDictionary *)info{
	    [imageView setImage:[info objectForKey:AvatarPickerImage]];
	    [urlLabel setText:[NSString stringWithFormat:@"%@",[info objectForKey:AvatarPickerURLString]]];
	    [self dismissModalViewControllerAnimated:YES];
	}
	-(void)AvatarPickerControllerDidCancel:(AvatarPickerPlus *)picker{
	    [self dismissModalViewControllerAnimated:YES];
	}

	/////////////////////////
	//    Advanced Setup   //
	/////////////////////////
	
    -(void)showAvatarPickerPlus{
    	AvatarPickerPlus *picker = [[AvatarPickerPlus alloc] init];
	    [picker setDelegate:self];
	    [picker setDefaultAccessToken:@"YOUR_ACCESS_TOKEN"];
    	[picker setAllowedServices:APPAllowFacebook|APPAllowTwitter|APPAllowGravatar];
    	[picker setAvatarPath:[NSString stringWithFormat:@"/%@",userID]]
	    [self presentModalViewController:picker animated:YES];
	}
	-(void)AvatarPickerController:(AvatarPickerPlus *)picker didFinishPickingMediaWithInfo:(NSDictionary *)info{
	    [imageView setImage:[info objectForKey:AvatarPickerImage]];
	    [urlLabel setText:[NSString stringWithFormat:@"%@",[info objectForKey:AvatarPickerURLString]]];
	    [self dismissModalViewControllerAnimated:YES];
	}
	-(void)AvatarPickerControllerDidCancel:(AvatarPickerPlus *)picker{
	    [self dismissModalViewControllerAnimated:YES];
	}
```
