# Sentiance SDK Starter Login
A simple login view application that uses the Sentiance SDK inside a Swift project.
   
Steps applied: [Sentiance iOS SDK docs](https://audience.sentiance.com/docs/sdk/ios/integration)

## Login flow

In a login view application, you will want to start the SDK only if the user is logged in. Most of the time, you will run the SDK from the AppDelegate, therefore you need to make sure that it doesn't get started if the user hasn't logged in yet. The same logic applies once the user has passed the login view, at that point you should start the SDK. 
Once the user is logged in, the SDK should always start from the AppDelegate.

## To run this project:
1.  Clone this repository
2.  Download and extract the latest framwork file from the [sentiance ios sdk docs](https://audience.sentiance.com/docs/sdk/ios/integration#download-sdk)
3.  Place the extracted framework in the repository root path
4.  [Create a developer account here](https://developers.sentiance.com/)
5.  [Register a Sentiance application here](https://developers.sentiance.com/apps) to obtain an application ID and secret
6.  `open SDKStarter.xcodeproj`
7.  In `SDKStarter/AppDelegate.swift`: replace `APP_ID` and `APP_SECRET` with the credentials from the application you added in step 5.
8.  Clean, build and run the application on your device



## More info
- [Full documentation on the Sentiance SDK](https://developers.sentiance.com/docs)
- [Developer signup](https://developers.sentiance.com/)
