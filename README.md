# Sentiance SDK Starter Login
A simple login view application that uses the Sentiance SDK inside a Swift project.
   
Steps applied: [Sentiance iOS SDK docs](https://audience.sentiance.com/docs/sdk/ios/integration)

## Login flow

In a login view application, you will want to start the SDK only if the user is logged in. Most of the time, you will run the SDK from the AppDelegate, therefore you need to make sure that it doesn't get started if the user hasn't logged in yet. The same logic applies once the user has passed the login view, at that point you should start the SDK. 
Once the user is logged in, the SDK should always start from the AppDelegate.

## To run this project:
1. Request a developer account by [contacting Sentiance](mailto:support@sentiance.com).
2. Grab your test app credentials from [here](https://insights.sentiance.com/#/apps).
3. Download and extract the latest framwork file from the [sentiance ios sdk docs](https://docs.sentiance.com/sdk/getting-started/ios-sdk/include-sdk)
4. Place the extracted framework in the repository root path
5. `open SDKStarter.xcodeproj`
6. In `SDKStarter/AppDelegate.swift`: replace `APP_ID` and `APP_SECRET` with the credentials from the application you added in step 2.
7. Clean, build and run the application on your device



## More info
- [Full documentation on the Sentiance SDK](https://docs.sentiance.com/)
