//
//  AvatarPickerPlus.h
//  ChuteSDKDevProject
//
//  Created by Brandon Coston on 4/25/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "GetChute.h"

enum {
    APPAllowFacebook    = 1<<0,
    APPAllowTwitter     = 1<<1,
    APPAllowInstagram   = 1<<2,
    APPAllowFlickr      = 1<<3,
    APPAllowPicasa      = 1<<4,
    APPAllowGravatar    = 1<<5
};
typedef NSUInteger AvatarPickerPlusAllowedServices;

#define AvatarPickerImage   @"APPDictionaryImage"
#define AvatarPickerURLString     @"APPDictionaryURLString"

enum {
    PhotoPickerPlusSourceTypeAll,
    PhotoPickerPlusSourceTypeLibrary,
    PhotoPickerPlusSourceTypeCamera,
    PhotoPickerPlusSourceTypeNewestPhoto
};
typedef NSUInteger PhotoPickerPlusSourceType;

@protocol AvatarPickerPlusLoginDelegate;
@protocol PhotoPickerPlusDelegate;
@protocol AvatarPickerPlusUploaderDelegate;
@protocol AvatarPickerPlusDelegate;

@interface PhotoPickerPlus : GCUIBaseViewController <UIImagePickerControllerDelegate, UINavigationControllerDelegate, UIActionSheetDelegate>

@property (nonatomic) BOOL typePicked;

//The delegate used for returning image info
@property (nonatomic, assign) NSObject <PhotoPickerPlusDelegate> *delegate;

@property (nonatomic) BOOL appeared;

//set to the source of the image selected
@property (nonatomic) PhotoPickerPlusSourceType sourceType;
@property (nonatomic) UIModalPresentationStyle presentationStyle;

@property (nonatomic) BOOL multipleImageSelectionEnabled;  //Allows users to select multiple images.  Requires location services for device photos.
@property (nonatomic) BOOL useStandardDevicePicker;  //Use standard UIImagePicker for device photos only allows single image selection from device but doesn't require location services.
@property (nonatomic) BOOL offerLatestPhoto;    //Offer option to use latest photo.  Note that this will require location serivices to work.

@end

@interface AccountViewController : GCUIBaseViewController <UIImagePickerControllerDelegate, UINavigationControllerDelegate, UITableViewDataSource, UITableViewDelegate>

@property (nonatomic, assign) NSObject <PhotoPickerPlusDelegate> *delegate;
@property (nonatomic, assign) PhotoPickerPlus *P3;

@property (nonatomic, retain) NSArray *photoAlbums;
@property (nonatomic, retain) NSArray *accounts;

@property (nonatomic, retain) UITableView *accountsTable;

@property (nonatomic) int accountIndex;

@property (nonatomic) BOOL multipleImageSelectionEnabled;
@property (nonatomic) BOOL useStandardDevicePicker;

-(UIView*)tableView:(UITableView *)tableView viewForIndexPath:(NSIndexPath*)indexPath;

@end

@interface AccountLoginViewController : GCUIBaseViewController <UIWebViewDelegate>

@property (nonatomic, retain) UIWebView *AddServiceWebView;
@property (nonatomic, retain) NSString *service;
@property (nonatomic, assign) NSObject <AvatarPickerPlusLoginDelegate> *delegate;

@end

@interface AlbumViewController : GCUIBaseViewController <UITableViewDataSource, UITableViewDelegate>

@property (nonatomic, assign) NSObject <PhotoPickerPlusDelegate> *delegate;
@property (nonatomic, assign) PhotoPickerPlus *P3;

@property (nonatomic, retain) NSArray *albums;

@property (nonatomic, retain) UITableView *albumsTable;

@property (nonatomic) BOOL multipleImageSelectionEnabled;
@property (nonatomic) BOOL useStandardDevicePicker;

@property (nonatomic, assign) NSDictionary *account;

-(UIView*)tableView:(UITableView *)tableView viewForIndexPath:(NSIndexPath*)indexPath;

@end

@interface PhotoViewController : GCUIBaseViewController <UITableViewDataSource, UITableViewDelegate>

@property (nonatomic, assign) NSObject <PhotoPickerPlusDelegate> *delegate;
@property (nonatomic, assign) PhotoPickerPlus *P3;

@property (nonatomic, retain) NSArray *photos;
@property (nonatomic, retain) NSMutableSet *selectedAssets;

@property (nonatomic, retain) UITableView *photosTable;

@property (nonatomic, retain) UIView *photoCountView;
@property (nonatomic, retain) UILabel *photoCountLabel;

@property (nonatomic) BOOL multipleImageSelectionEnabled;
@property (nonatomic) BOOL useStandardDevicePicker;
@property (nonatomic, assign) NSDictionary *account;
@property (nonatomic, assign) NSDictionary *album;
@property (nonatomic, assign) ALAssetsGroup *group;

-(UIView*)tableView:(UITableView *)tableView viewForIndexPath:(NSIndexPath*)indexPath;

@end

@protocol PhotoPickerPlusDelegate <NSObject>

-(void)PhotoPickerPlusController:(PhotoPickerPlus *)picker didFinishPickingMediaWithInfo:(NSDictionary *)info;
-(void)PhotoPickerPlusControllerDidCancel:(PhotoPickerPlus *)picker;
-(void)PhotoPickerPlusController:(PhotoPickerPlus *)picker didFinishPickingArrayOfMediaWithInfo: (NSArray*)info;

@end


@interface AvatarPickerPlus : GCUIBaseViewController 

@property (nonatomic, assign) UIViewController <AvatarPickerPlusDelegate> *delegate;
@property (nonatomic, retain) NSString *avatarPath;
@property (nonatomic) AvatarPickerPlusAllowedServices allowedServices;
@property (nonatomic) BOOL useStandardDevicePicker;
@property (nonatomic, retain) NSString *defaultAccessToken;

@end

@interface AvatarPickerAvatarController : GCUIBaseViewController <PhotoPickerPlusDelegate, AvatarPickerPlusLoginDelegate, UITableViewDataSource, UITableViewDelegate, UIAlertViewDelegate> 

@property (nonatomic, assign) AvatarPickerPlus *APP;
@property (nonatomic, assign) UIViewController <AvatarPickerPlusDelegate> *delegate;
@property (nonatomic, retain) NSArray *avatarArray;
@property (nonatomic, retain) UITableView *avatarTable;
@property (nonatomic) AvatarPickerPlusAllowedServices allowedServices;
@property (nonatomic) BOOL useStandardDevicePicker;
@property (nonatomic, retain) NSString *avatarPath;
@property (nonatomic, retain) NSString *defaultAccessToken;

@end

@interface AvatarPickerAssetUploader : NSObject

@property (nonatomic, retain) UIImage *asset;
@property (nonatomic, retain) NSString *location;
@property (nonatomic, retain) NSString *assetURL;
@property (nonatomic, assign) NSObject <AvatarPickerPlusUploaderDelegate> *delegate;
@property (nonatomic, retain) NSString *defaultAccessToken;

-(void)uploadWithPath:(NSString*)pathComponent;

@end

@interface AvatarPickerImageCropper : GCUIBaseViewController <UIScrollViewDelegate, AvatarPickerPlusUploaderDelegate>

@property (nonatomic, assign) AvatarPickerPlus *APP;
@property (nonatomic, assign) UIViewController <AvatarPickerPlusDelegate> *delegate;
@property (nonatomic, retain) AvatarPickerAssetUploader *uploader;
@property (nonatomic, retain) UIImage *originalImage;
@property (nonatomic, retain) NSString *originalURL;
@property (nonatomic) CGSize size;
@property (nonatomic) float minScale;
@property (nonatomic) float maxScale;
@property (nonatomic, retain) UIScrollView *scroller;
@property (nonatomic) CGRect cropRect;
@property (nonatomic, retain) UIImageView *image;
@property (nonatomic, retain) NSString *avatarPath;
@property (nonatomic, retain) NSString *defaultAccessToken;

@end

@interface APPRequest : GCRequest

@property (nonatomic, retain) NSString *defaultAccessToken;

@end

@protocol AvatarPickerPlusUploaderDelegate <NSObject>

-(void)APPUploaderDidGetToken:(AvatarPickerAssetUploader*)uploader;
-(void)APPUploaderDidFinishUpload:(AvatarPickerAssetUploader*)uploader;
-(void)APPUploaderDidCompleteUpload:(AvatarPickerAssetUploader*)uploader;
-(void)APPUploaderImageAlreadyUploaded:(AvatarPickerAssetUploader*)uploader;

@end

@protocol AvatarPickerPlusDelegate <NSObject>

-(void)AvatarPickerController:(AvatarPickerPlus *)picker didFinishPickingMediaWithInfo:(NSDictionary *)info;
-(void)AvatarPickerControllerDidCancel:(AvatarPickerPlus *)picker;

@end

@protocol AvatarPickerPlusLoginDelegate <NSObject>

-(void)AvatarServiceLoginDidComplete:(AccountLoginViewController*)loginController;

@end