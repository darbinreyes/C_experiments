/*
##### First draft definition of using P2D for HP REST CONFIG ###################

10.7.2 HP REST CONFIG ParameterTypeGuid

The following ParameterTypeGuid value provides the support for
exchanging HTTP messages between the platform (Producer) and driver (consumer).
The intent is to support RESTful configuration of a device driver on top of
the P2D protocol.

GUID
       #define EFI_PLATFORM_TO_DRIVER_CONFIGURATION_HP_REST_CONFIG_GUID \
         {XxXxxxxxxxxxxxxxxx}}

The a pointer to the following struct will be returned from a call Query() via
the parameter block argument.

//*******************************************************
//EFI_HP_REST_CONFIG_BLK
//*******************************************************
typedef struct {
EFI_HTTP_MESSAGE   *Request;  // Set by the platform. Upon return from Query(0), an HTTP request message containing a configuration request. The integer argument is the "Instance" number.
EFI_HTTP_MESSAGE   *Response; // Set by the driver. Upon a call to Response(0), an HTTP response message containing the result of the configuration request provided to the driver from the platform on return from Query(0).
} EFI_HP_REST_CONFIG_BLK;

--Restrictions imposed by the P2D protocol:

Driver is always the caller.
Platform is always the callee.

Thus the platform sends data to the driver via output arguments and return values.
Thus the platform receives data via input arguments.

--Only the platform makes HTTP requests.
--Only the driver makes HTTP responses.
--Thus the platform is like an HTTP client. The driver is like an HTTP server.

Each HTTP Request will only use 1 of 2 possible HTTP methods:
1. GET. This means the platform wants the driver to PRODUCE the resource identified by URI.
2. PUT. This means the platform wants the driver to CONSUME the resource identified by URI.
   The resource to consume is given in the PUT request body.

//The above methods are chosen arbitrarily. Are there any reasons to define them
differently? e.g POST vs. PUT?

All other HTTP methods should be ignored by the driver and treated as an error. The
platform will not use any other HTTP method in its requests.

When the driver calls Query(0):
The platform returns an HTTP request in the ParameterBlock. This HTTP request
describes what operations the platform is asking of the driver.

When the driver calls Response(0):
The platform will inspect and/or use the data given to it from the driver in the
form of an HTTP response. The HTTP response will be provided to the platform
in the ParameterBlock argument.

Every call to Query() will return a pointer to a EFI_HP_REST_CONFIG_BLK. Assume
the following variable is declared:

EFI_HP_REST_CONFIG_BLK HpRestConfigBlk;

The platform will perform the following general steps before returning from Query().


EFI_HTTP_REQUEST_DATA         RequestData;
EFI_HTTP_MESSAGE              Request;
EFI_HTTP_HEADER               RequestHeader;

//
// Init the HpRestConfigBlk.Request
//

//
// Set the request method and URI.
//
RequestData.Method = HttpMethodGet;
RequestData.Url = L"/Providers";

//
// Set the request headers.
//
RequestHeader.FieldName  = "ContentType"; // Arbitrary example of setting header value in request.
RequestHeader.FieldValue = "application/json";

//
// This request message has no body/content.
//

//
// Set full request struct.
//
Request.Data = &RequestData;
Request.HeaderCount = 1;
Request.Headers = &RequestHeader;
Request.BodyLength = 0;
Request.Body = NULL;

HpRestConfigBlk.Request = &Request;



EFI_HTTP_RESPONSE_DATA        ResponseData;






*/



