# node-rfc

Asynchronous, non-blocking [SAP NetWeawer RFC SDK](https://support.sap.com/en/product/connectors/nwrfcsdk.html) client bindings for [Node.js](http://nodejs.org/), providing convenient ABAP business logic consumption from NodeJS.

[![NPM](https://nodei.co/npm/node-rfc.png?downloads=true&downloadRank=true)](https://nodei.co/npm/node-rfc/)

[![license](https://img.shields.io/badge/License-Apache%202.0-blue.svg)](https://opensource.org/licenses/Apache-2.0)
[![N-API v6 Badge](https://github.com/nodejs/abi-stable-node/raw/doc/assets/N-API%20v6%20Badge.svg?sanitize=true)](https://github.com/nodejs/abi-stable-node/)
[![release](https://img.shields.io/npm/v/node-rfc.svg)](https://www.npmjs.com/package/node-rfc)
[![downloads](https://img.shields.io/github/downloads/sap/node-rfc/total.svg)](https://www.npmjs.com/package/node-rfc)
[![dpm](https://img.shields.io/npm/dm/node-rfc.svg)](https://www.npmjs.com/package/node-rfc)
[![REUSE status](https://api.reuse.software/badge/github.com/SAP/node-rfc)](https://api.reuse.software/info/github.com/SAP/node-rfc)
[![CII Best Practices](https://bestpractices.coreinfrastructure.org/projects/4350/badge)](https://bestpractices.coreinfrastructure.org/projects/4350)

## Key features

-   Based on [N-API](https://github.com/nodejs/node-addon-api) standard
-   Stateless and stateful connections (multiple function calls in the same ABAP session (same context))
-   Async/await, promise and callback API
-   ECMAScript, TypeScript
-   Sequential and parallel calls, using one or more clients
-   Automatic conversion between NodeJS and ABAP datatypes
-   Direct and managed connections (connection pool)
-   Throughput monitoring: number of calls, bytes sent/received, application/total time; SAP NWRFC SDK >= 7.53 required

## Content

-   **[Supported Platforms](#supported-platforms)**
-   **[Prerequisites](#prerequisites)**
-   **[Installation](#installation)**
-   **[Getting started](#getting-started)**
-   **[Usage](doc/usage.md)**
    -   **[Authentication](doc/authentication.md)**
    -   **[sapnwrfc.ini](doc/usage.md#addon)**
    -   **[Client](doc/usage.md#client-toc)**
    -   **[Connection Pool](doc/usage.md#connection-pool)**
    -   **[Throughput](doc/usage.md#throughput)**
-   **[API](doc/api.md)**
    -   **[Connection Pool](doc/api.md#connection-pool)**
    -   **[Client](doc/api.md#client)**
    -   **[Throughput](doc/api.md#throughput)**
-   **[Troubleshooting](doc/troubleshooting.md)**
-   **[More resource and info about SAP Connectors and RFC communication](#resources)**
-   **[Code of Conduct](CODE_OF_CONDUCT.md)**
-   **[Contributing](#contributing)**
-   **[License](#license)**

## Supported platforms

-   [Current and active nodejs LTS releases](https://github.com/nodejs/LTS)

-   The _node-rfc_ connector can be [built from source](#setup) on all platforms supported both by [SAP NW RFC SDK](https://launchpad.support.sap.com/#/notes/2573790) and by [nodejs](https://github.com/nodejs/node/blob/master/BUILDING.md#supported-platforms-1)

-   Pre-built binaries are provided for [active nodejs LTS releases](https://github.com/nodejs/LTS), for 64 bit Windows 10, macOS 10.15 and [Centos 7 based docker container](https://github.com/SAP/fundamental-tools/tree/master/docker)

Other platforms and frameworks:

-   SAP Cloud Platform, AWS Lambdas, heroku ...: Create SAP feature request for `SAP Cloud Platform Connectivity Service` sub-topic of the [SAP Cloud Platform - Integration Suite](https://influence.sap.com/sap/ino/#/campaign/2282)
-   [Electron](doc/frameworks/electron-quick-start)
-   [NW.js](doc/frameworks/nwjs-quick-start)
-   [Node-RED](https://github.com/PaulWieland/node-red-contrib-saprfc)
-   [Sails JS](https://github.com/dcolley/sailsjs-node-rfc)

## Prerequisites

### All platforms

-   SAP NW RFC SDK C++ binaries must be downloaded (SAP partner or customer account required) and locally installed ([installation instructions](doc/installation.md#sap-nwrfc-sdk-installation). More information on [SAP NW RFC SDK section on SAP Support Portal](https://support.sap.com/en/product/connectors/nwrfcsdk.html). Using the latest version is reccomended as SAP NW RFC SDK is fully backwards compatible, supporting all NetWeaver systems, from today S4, down to R/3 release 4.6C.

-   Build toolchain requires [CMake](https://cmake.org/)

-   Build from source on older Linux systems, may require `uchar.h` file, attached to [SAP OSS Note 2573953](https://launchpad.support.sap.com/#/notes/2573953), to be copied to SAP NW RFC SDK include directory.

### Windows

-   [Visual C++ Redistributable](https://www.microsoft.com/en-US/download/details.aspx?id=40784) is required for runtime. The version is given in [SAP Note 2573790 - Installation, Support and Availability of the SAP NetWeaver RFC Library 7.50](https://launchpad.support.sap.com/#/notes/2573790)

-   Build toolchain requires [Microsoft C++ Build Tools](https://aka.ms/buildtools), the latest version reccomended

### macOS

-   Disable macOS firewall stealth mode ([Can't ping a machine - why?](https://discussions.apple.com/thread/2554739)):

```shell
sudo /usr/libexec/ApplicationFirewall/socketfilterfw --setstealthmode off
```

-   Remote paths must be set in SAP NWRFC SDK for macOS: [documentation](http://sap.github.io/PyRFC/install.html#macos)

-   When the node-rfc is started for the first time, the popups come-up for each NWRFC SDK library, to confirm it should be opened. If SDK is installed in admin folder, the node-rfc app shall be that first time started with admin privileges, eg. `sudo -E`

## Installation

More info: **[Installation](doc/installation.md)**

:exclamation: The npm installation and build from source, work only with NodeJS versions with minimum N-API 6: [NodeJS/N-API version matrix](https://nodejs.org/api/n-api.html#n_api_n_api_version_matrix). Usage works with all NodeJS versions supported by `node-rfc`.

After the SAP NW RFC SDK is installed on your system, the `node-rfc` can be installed from npm:

```shell
npm install node-rfc
```

Alternatively, when the `node-rfc` package is not provided for your platform for example, you can build the package from source:

```shell
git clone --single-branch https://github.com/SAP/node-rfc.git
cd node-rfc
npm install
npm run addon # rebuild native addon
npm run ts    # rebuild typescript wrapper
```

## Getting started

More info: **[Usage](doc/usage.md)** and **[API](doc/api.md)**

In order to call remote enabled ABAP function module, we need to create a `node-rfc` client instance with valid logon credentials, connect to SAP ABAP NetWeaver system and then invoke a remote enabled ABAP function module from nodejs. Async example below shows basic principles and you can check the documentationand unit tests for more examles.

Add your ABAP system destintion to **sapnwrfc.ini** file in your working directory:

```ini
DEST=MME
USER=demo
PASSWD=welcome
ASHOST=myhost
SYSNR=00
CLIENT=620
LANG=EN
```

Call the ABAP RFM. When in doubt about RFM parameters' structure, use **[rfmcall](https://github.com/SAP/fundamental-tools/tree/master/tools/rfmcall)**:

```javascript
const noderfc = require("node-rfc");

const pool = new noderfc.Pool({ connectionParameters: { dest: "MME" } });

(async () => {
    try {
        // get a client connection instance
        const client = await pool.acquire();

        // invoke ABAP function module, passing structure and table parameters

        // ABAP structure
        const structure = {
            RFCINT4: 345,
            RFCFLOAT: 1.23456789,
            RFCCHAR4: "ABCD",
            RFCDATE: "20180625", // ABAP date format
            // or RFCDATE: new Date('2018-06-25'), // as JavaScript Date object, with clientOption "date"
        };
        // ABAP table
        let table = [structure];

        const result = await client.call("STFC_STRUCTURE", {
            IMPORTSTRUCT: structure,
            RFCTABLE: table,
        });

        // check the result
        console.log(result);
    } catch (err) {
        // connection and invocation errors
        console.error(err);
    }
})();
```

Finally, the connection is closed automatically when the instance is deleted by the garbage collector or by explicitly calling the `client.close()` method of the direct client, or `client.release()` or `pool.release()` for the managed client.

<a name="resources"></a>

## More resource and info about ABAP Connectors and RFC Communication

Highly reccomended series of three insightful articles about RFC communication and SAP NW RFC Library, published in the SAP Professional Journal (SPJ):

-   **[Part I RFC Client Programming](https://wiki.scn.sap.com/wiki/x/zz27Gg)**
-   **[Part II RFC Server Programming](https://wiki.scn.sap.com/wiki/x/9z27Gg)**
-   **[Part III Advanced Topics](https://wiki.scn.sap.com/wiki/x/FD67Gg)**

and more:

-   **[SAP NWRFC SDK 7.50 Programming Guide](https://support.sap.com/content/dam/support/en_us/library/ssp/products/connectors/nwrfcsdk/NW_RFC_750_ProgrammingGuide.pdf)**
-   **[ABAP Connectors](https://support.sap.com/en/product/connectors.html)**
-   **[SAP NWRFC SDK](https://support.sap.com/en/product/connectors/nwrfcsdk.html)**
-   **[node-addon-api](https://github.com/nodejs/node-addon-api)**

## Known Issues

-   NAPI Type checks [nodejs/node-addon-api/#265](https://github.com/nodejs/node-addon-api/issues/265)

## How to obtain support

If you encounter an issue or have a feature request, you can create a [ticket](https://github.com/SAP/node-rfc/issues).

Check out the SCN Forum (search for "node-rfc") and stackoverflow (use the tag "node-rfc"), to discuss code-related problems and questions.

## **Contributing**

We appreciate contributions from the community to **node-rfc**!
See [CONTRIBUTING.md](CONTRIBUTING.md) for more details on our philosophy around extending this module.
