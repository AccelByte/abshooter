
# Build and upload DS docker image

Here's a brief explanation about how to build Shooter Game Server as docker image and then upload it to Amazon ECR.
We're assuming that you using Win10 to compiling these and Linux as the Server.

## Requirements

`1.` [Docker](https://www.docker.com/get-started) for build the image.
`2.` [AWS CLI](https://aws.amazon.com/cli/) to loging in your docker to your aws account.
`3.` [Visual Studio 2017](https://visualstudio.microsoft.com/downloads/) for the IDE and build the server.
`4.` `Unreal Engine 4.21` build from source, please refer to [here](https://wiki.unrealengine.com/GitHub_Setup) to get UE4 source code. After you get the access to the code, please build the source from this stage: `f7626ddd147fe20a6144b521a26739c863546f4a`
`5.` And `clang` for cross-compiling from windows to linux, please refer to [here](https://wiki.unrealengine.com/Compiling_For_Linux) for the documentation.

## Step by step
`1.` After you get all the requirements, first thing to do is to build the server. You can the package using `ShooterGame\package-debut.bat`, make sure you change the setting to fit your project, and change the `targetplatform` to `Linux`.
`2.` After the package is done, you will get `LinuxNoEditor` folder inside the `ShooterGame\Output` folder directory. We will use it as our client base. Copy the whole `LinuxNoEditor` folder to `DSbuild\prep`.
`3.` Now for the server, open visual studio solution on `ShooterGame.sln`, change the Solution Configurations to `Development Server` or `Shipping Server`, choose `Development Server` for easier debugging. And change the Solution Platforms to `Linux`, and then build it.
`4.` After the build is done, you should get these 4 `ShooterGameServer` files under `ShooterGame\Binaries\Linux` directory. Now go to `DSbuild\prep\LinuxNoEditor\ShooterGame\Binaries\Linux`, empty that folder and replace it with those 4 files.
`5.` Now you're ready to build the docker image, but before that make sure you've already set your creds on `DSBuild\prep\LinuxNoEditor\run.sh`. After you done that, just simply open your docker command-line on `DSbuild` directory and write this command : `docker build -t <YOUR-IMAGE-TAG>:<YOUR-IMAGE-VERSION> -f "Dockerfile" "prep"`.
`6.` You should have your docker image now, you can check it using command `docker images`. Now refer to this [documentation](https://docs.aws.amazon.com/AmazonECR/latest/userguide/docker-push-ecr-image.html) to upload the image to your ECR.