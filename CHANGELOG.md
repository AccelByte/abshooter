# Changelog
## 2.3.0 (Unreleased)
## Added
- AccelByte Justice SDK 2.34.0

## Fixed
- Fixed game server code compatibility with new SDK
- Fixed game client cannot connect with game server local & cloud

## 2.2.0 (2021-02-23)

## Added
- AccelByte Justice SDK 2.28.1

## Fixed
- Fixed game code compatibility with new SDK
- Fixed compilation error on clang build upgrade server version

## 2.1.0 (2020-10-01)
- Support Unreal Engine 4.25
- Controller Support required for console support


## 2.0.1 (2020-08-04)
## Added
- AccelByte Justice SDK 2.18.3
- Agones SDK

## 2.0.0 (2020-07-23)
## Added
- Moved UI from Slate to Partial UMG
- Converted Lobby UI from Slate to UMG
- Converted Achievment UI from Slate to UMG
- Converted Leaderboard UI from Slate to UMG
- Converted Matchmaking functionality to UMG
- Modified FFA Game Mode to work with AccelByte System
- FFA Game Mode version of Highrise named FFA_Highrise
- Save Credentials Functionality to Login
- Game Mode Selection on the Lobby
- Region Selection on the Lobby
- Counter for Finding Matchmaking
- Countdown for when Matchmaking has been Found
- Created Packaging and Build Script for Client and Server

## Fixed
- Server closing instantly after Match ended
- Returning to Main Menu after match ended did not work
- Clean up operation for the main game classes

## Removed
- Old Highrise Map, now renamed to TDM_Highrise

## 1.8.1 (2020-07-13)
## Fixed
- Clean up operation for the main game classes

## 1.8.1 (Unreleased)
## Added
- AccelByte Justice SDK 2.18.3
- Agones SDK

## 1.8.0 (2020-06-15)
## Added
- Enable Steamworks and OnlineSubsystemSteam within project
- Login using Steam account

## 1.7.0 (2020-06-09)
## Added
- AccelByte SDK 2.14.0
- Client & server game telemetry 
- SFX and animation on QoS refresh button pressed
- In game notification when a player quits the current match
- AccelByte SDK 2.12.0
- Leaderboard implementation
- Pop up message to notify the cause of matchmaking failure
- Lobby connection checker on matchmaking
## Fixed
- Player stuck after match if the match result is draw
- Fix friendlist entry duplicated
- Fix incoming message is not displayed
- Fix lobby chat tab shows user ID
- Fix add friend displayname shows user ID
- Cleanup screenshot cache after match/back to main menu
- Retry upload accesses empty array index

## 1.6.0 (2020-05-27)
## Added
- Menu to login using username password
- Region selector (QoS) to select Dedicated Server
- Player statistic menu
- AccelByte SDK 2.7.0
- Statistic service added
- QoS implementation for matchmaking
- ShooterGameConfig class
## Fixed
- Screenshot menu stuck on back from gameplay to main menu
- Search user return empty array handler
- Server update MVP statistic bug
- StartMatch button missing if user has no user profile
- Inventory & store item thumbnail
- DS dockerfile entrypoint
- Player enter level/match multiple times bug
- Local play mode for client and server
- Linux compile error (pragma once)
- LocalDS deregister itself on 409 when try to register
- Player entering DS too fast, delay added
- DS heartbeat match info handler
- Handle "BUSY" DS Notif
- Network error retry
- Podname server
- DS registration on spawned
## Removed
- Claim match from DedicatedServer
- DS register and shutdown logic
- Determine winner on end game (temporary)
- Deregister server on end game


## 1.5.0 (2019-11-25)
## Fixed
- Update changes on Ecommerce
- Fix discount still appear after expired time

## 1.4.0 (2019-11-11)
## Fixed
- Follow Basic API Standardization
- Follow Statistic API Standardization

## 1.3.0 (2019-10-14)
## Fixed
- Follow IAM API Standardization
- Default User Profile not filling 'firstname' field
- Change CurrencyCode from `ShooterGameCoin` to `SGC`
- Change notification topic from `0004` to `SHOOTER_GAME`

## 1.2.1 (2019-10-08)
## Fixed
- Metadata are saved after delete screenshot.

## 1.2.0 (2019-10-08)
## Added
- Adding DS Build:
  - DS communicating to DSM
  - Opening TCP and UDP at port 15000-16000
  - Shutting down after no party member on it
- Using API Gateway
- Implementing Statistic GET
- Showing Game Profile's display name instead of user profile's
## Fixed
- Leader can leave party
- When matchmaking, party member can't leave party
