// Copyright (c) Microsoft Corporation.
// All rights reserved.
//
// This code is licensed under the MIT License.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.


#import <Foundation/Foundation.h>

@interface ADAuthorityValidation : NSObject<ADRequestContext> {
    NSMutableDictionary *_validatedAdfsAuthorities;
    NSMutableSet *_validatedADAuthorities;
    
    NSUUID *_correlationId;
    NSString *_telemetryRequestId;
}

+ (ADAuthorityValidation *)sharedInstance;

/*!
 This is for caching of valid authorities.
 For ADFS, it will cache the authority and the domain. 
 For AAD, it will simply cache the authority
 */
// Cache - ADFS
- (BOOL)addValidAuthority:(NSString *)authority domain:(NSString *)domain;
- (BOOL)isAuthorityValidated:(NSString *)authority domain:(NSString *)domain;
// Cache - AD
- (BOOL)isAuthorityValidated:(NSString *)authorityHost;
- (BOOL)addValidAuthority:(NSString *)authorityHost;

/*!
 Validates an authority.
 
 @param authority            The AAD or ADFS authority. Example: @"https://login.windows.net/contoso.com"
 @param upn                  User principal name. This is used for ADFS validation.
 @param completionBlock      The block to execute upon completion.

 */
- (void)validateAuthority:(NSString *)authority
                      upn:(NSString *)upn
          completionBlock:(void (^)(BOOL validated, ADAuthenticationError *error))completionBlock;

// Convenience method
- (void)validateAuthority:(NSString *)authority
          completionBlock:(void (^)(BOOL validated, ADAuthenticationError *error))completionBlock;

// Validation for ADFS authority.
- (void)validateADFSAuthority:(NSString *)authority
                       domain:(NSString *)domain
              completionBlock:(void (^)(BOOL validated, ADAuthenticationError *error))completionBlock;


// Validation for AAD authority
- (void)validateAuthority:(NSString *)authority
            authorityHost:authorityHost
          completionBlock:(void (^)(BOOL validated, ADAuthenticationError *error))completionBlock;

// ADRequestContext
@property(retain, nonatomic) NSUUID *correlationId;
@property(retain, nonatomic) NSString *telemetryRequestId;

@end
