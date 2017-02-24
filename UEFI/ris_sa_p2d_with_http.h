//############################ HTTP-like revision.
///
/// EFI_HTTP_TOKEN
///
typedef struct {
  ///
  /// This Event will be signaled after the Status field is updated by the EFI HTTP
  /// Protocol driver. The type of Event must be EFI_NOTIFY_SIGNAL. The Task Priority
  /// Level (TPL) of Event must be lower than or equal to TPL_CALLBACK.
  ///
  EFI_EVENT                     Event;
  ///
  /// Status will be set to one of the following value if the HTTP request is
  /// successfully sent or if an unexpected error occurs:
  ///   EFI_SUCCESS:      The HTTP request was successfully sent to the remote host.
  ///   EFI_ABORTED:      The HTTP request was cancelled by the caller and removed from
  ///                     the transmit queue.
  ///   EFI_TIMEOUT:      The HTTP request timed out before reaching the remote host.
  ///   EFI_DEVICE_ERROR: An unexpected system or network error occurred.
  ///
  EFI_STATUS                    Status;
  ///
  /// Pointer to storage containing HTTP message data.
  ///
  EFI_HTTP_MESSAGE              *Message;
} EFI_HTTP_TOKEN;


///
/// EFI_HTTP_MESSAGE
///
typedef struct {
  ///
  /// HTTP message data.
  ///
  union {
    ///
    /// When the token is used to send a HTTP request, Request is a pointer to storage that
    /// contains such data as URL and HTTP method.
    ///
    EFI_HTTP_REQUEST_DATA       *Request;
    ///
    /// When used to await a response, Response points to storage containing HTTP response
    /// status code.
    ///
    EFI_HTTP_RESPONSE_DATA      *Response;
  } Data;
  ///
  /// Number of HTTP header structures in Headers list. On request, this count is
  /// provided by the caller. On response, this count is provided by the HTTP driver.
  ///
  UINTN                         HeaderCount;
  ///
  /// Array containing list of HTTP headers. On request, this array is populated by the
  /// caller. On response, this array is allocated and populated by the HTTP driver. It
  /// is the responsibility of the caller to free this memory on both request and
  /// response.
  ///
  EFI_HTTP_HEADER               *Headers;
  ///
  /// Length in bytes of the HTTP body. This can be zero depending on the HttpMethod type.
  ///
  UINTN                         BodyLength;
  ///
  /// Body associated with the HTTP request or response. This can be NULL depending on
  /// the HttpMethod type.
  ///
  VOID                          *Body;
} EFI_HTTP_MESSAGE;


//*******************************************************
//EFI_HP_REST_CONFIG_BLK
//*******************************************************
typedef struct {
EFI_HTTP_MESSAGE   Request;
EFI_HTTP_MESSAGE   Response;
} EFI_HP_REST_CONFIG_BLK;

//query
typedef
EFI_STATUS
(EFIAPI *EFI_PLATFORM_TO_DRIVER_CONFIGURATION_QUERY)(
  IN CONST  EFI_PLATFORM_TO_DRIVER_CONFIGURATION_PROTOCOL *This,
  IN CONST  EFI_HANDLE  ControllerHandle,
  IN CONST  EFI_HANDLE  ChildHandle OPTIONAL,
  IN CONST  UINTN       *Instance,
  OUT       EFI_GUID    **ParameterTypeGuid,
  OUT       VOID        **ParameterBlock,
  OUT       UINTN       *ParameterBlockSize
);

//response
typedef
EFI_STATUS
(EFIAPI *EFI_PLATFORM_TO_DRIVER_CONFIGURATION_RESPONSE)(
  IN CONST  EFI_PLATFORM_TO_DRIVER_CONFIGURATION_PROTOCOL *This,
  IN CONST  EFI_HANDLE  ControllerHandle,
  IN CONST  EFI_HANDLE  ChildHandle OPTIONAL,
  IN CONST  UINTN       *Instance,
  IN CONST  EFI_GUID    *ParameterTypeGuid,
  IN CONST  VOID        *ParameterBlock,
  IN CONST  UINTN       ParameterBlockSize ,
  IN CONST  EFI_PLATFORM_CONFIGURATION_ACTION ConfigurationAction
);

/*

-General Notes.

Driver is always the caller.
Platform is always the callee.

Thus the platform sends data to the driver via output arguments and return values.
Thus the platform receives data via input arguments.

The following descriptions are from the perspective of the platform (callee).

-Only the platform makes HTTP requests.
The driver should never modify the HTTP request, it can only make copies of the
data if the driver wishes to make modifications to it. This includes
the restriction that the driver should never try to free any buffers in the HTTP request.

-Only the driver makes HTTP responses.

Thus the platform is like an HTTP client. The driver is like an HTTP server.



Each HTTP Request will only use 1 of 2 possible methods:
1. GET. This means the platform wants the driver to PRODUCE the resource identified by URI.
2. PUT. This means the platform wants the driver to CONSUME the resource identified by URI.
The resource to consume is given in the PUT request body.

The above methods are chosen arbitrarily. Are there any reasons to define them
differently? e.g POST vs. PUT?

All other HTTP methods should be ignored and treated as an error. The platform
will *not use any other HTTP method in its requests.

*Unless this spec it revised to include other methods if necessary.

When the driver calls Query():
The platform returns an HTTP request in the ParameterBlock. This HTTP request
describes what operations and/or data the platform is asking of the driver.

When the driver calls Response():
The platform will inspect and/or use the data given to it from the driver in the
form of an HTTP response. The HTTP response will be provided to the platform
in the ParameterBlock argument.


// NOTE: Use pre-conditions and post-conditions in the query()/response()
function headers in the context of using P2D for RIS.

Usage notes of RIS P2D should be in the form of an API documentation.

NEXT:
define parameter block
define parameter block usage.

HTTP UEFI spec question:
Why does the spec. require that the caller allocate the response body buffer?
Why not have the specify that the HTTP driver will allocate it and the
caller frees it just like the response headers. The HTTP driver will always know
the response body size, why not wait for the full body to arrive and then alloc.
a buffer to return it in a single call to response vs. asking for the next chunk
with NULL/0 fields in the request token.

NOTE: we can probably use the same HTTP UEFI spec language/description by simply
reversing the interpretation of caller/callee. i.e. The caller is a the platform
WRT to the parameter block argument, the callee is the driver.

The first HTTP request will always be a GET on /Providers. // use GET if-none-match? no, we still need the keep alive JSON.
///

driver calls Query(0,Request)
return from Query(0, Request=GET /Providers), Status=EFI_SUCCESS

driver calls Response(0,Response)
if(ProviderService->IsRegistered(Response)) {
  ProviderService->KeepAlive(Response);
  NEXT=ConsumeAll
} else { // not registered.
  ProviderService->Register(Response)
  NEXT=ProduceAllSchemasAndRegistries
}
return from Response(0, Request), Status=EFI_SUCCESS


///

//Think about the implications of a failed registration or keep alive and when actual requests to the RIS service will be made.

-RESOURCE CONSUME REQUESTS ON DRIVER
We have two options, non-blocking vs. blocking WRT to iLO RIS CHIFS.
1. All consumable resources have been obtained from the RIS resource tree before
the driver makes the first call to Query().
2. We GET a single consumable resource before returning from Query with the consume
request. We pass the resource to consume in the request body.

// we don't need the macro substitution in JSON if we provide that info. in request headers
of produce operations.

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
EFI_HTTP_MESSAGE   Request;
EFI_HTTP_MESSAGE   Response;
} EFI_HP_REST_CONFIG_BLK;

--Restrictions imposed by the P2D protocol:

Driver is always the caller.
Platform is always the callee.

Thus the platform sends data to the driver via output arguments and return values.
Thus the platform receives data via input arguments.

--Only the platform makes HTTP requests.

The driver should never modify the HTTP request, it can only make copies of the
data if the driver wishes to make modifications to it. This includes
the restriction that the driver should never try to free any buffers in the HTTP request.

Thus the platform is like an HTTP client. The driver is like an HTTP server.

Each HTTP Request will only use 1 of 2 possible methods:
1. GET. This means the platform wants the driver to PRODUCE the resource identified by URI.
2. PUT. This means the platform wants the driver to CONSUME the resource identified by URI.
The resource to consume is given in the PUT request body.

The above methods are chosen arbitrarily. Are there any reasons to define them
differently? e.g POST vs. PUT?

All other HTTP methods should be ignored and treated as an error. The platform
will not use any other HTTP method in its requests.

When the driver calls Query():
The platform returns an HTTP request in the ParameterBlock. This HTTP request
describes what operations and/or data the platform is asking of the driver.

When the driver calls Response():
The platform will inspect and/or use the data given to it from the driver in the
form of an HTTP response. The HTTP response will be provided to the platform
in the ParameterBlock argument.

Every call to Query() will return a pointer to a EFI_HP_REST_CONFIG_BLK. Assume
the following variable is declared:

EFI_HP_REST_CONFIG_BLK HpRestConfigBlk;

The platform will perform the following steps before returning from Query().

EFI_HTTP_REQUEST_DATA         RequestData;

// Set the
HpRestConfigBlk.Data = RequestData;

EFI_HTTP_RESPONSE_DATA        ResponseData;


-Only the driver makes HTTP responses.

Thus the platform is like an HTTP client. The driver is like an HTTP server.

///
/// EFI_HTTP_MESSAGE
///
typedef struct {
  ///
  /// HTTP message data.
  ///
  union {
    ///
    /// When the token is used to send a HTTP request, Request is a pointer to storage that
    /// contains such data as URL and HTTP method.
    ///
    EFI_HTTP_REQUEST_DATA       *Request;
    ///
    /// When used to await a response, Response points to storage containing HTTP response
    /// status code.
    ///
    EFI_HTTP_RESPONSE_DATA      *Response;
  } Data;
  ///
  /// Number of HTTP header structures in Headers list. On request, this count is
  /// provided by the caller. On response, this count is provided by the HTTP driver.
  ///
  UINTN                         HeaderCount;
  ///
  /// Array containing list of HTTP headers. On request, this array is populated by the
  /// caller. On response, this array is allocated and populated by the HTTP driver. It
  /// is the responsibility of the caller to free this memory on both request and
  /// response.
  ///
  EFI_HTTP_HEADER               *Headers;
  ///
  /// Length in bytes of the HTTP body. This can be zero depending on the HttpMethod type.
  ///
  UINTN                         BodyLength;
  ///
  /// Body associated with the HTTP request or response. This can be NULL depending on
  /// the HttpMethod type.
  ///
  VOID                          *Body;
} EFI_HTTP_MESSAGE;
///
/// EFI_HTTP_REQUEST_DATA
///
typedef struct {
  ///
  /// The HTTP method (e.g. GET, POST) for this HTTP Request.
  ///
  EFI_HTTP_METHOD               Method;
  ///
  /// The URI of a remote host. From the information in this field, the HTTP instance
  /// will be able to determine whether to use HTTP or HTTPS and will also be able to
  /// determine the port number to use. If no port number is specified, port 80 (HTTP)
  /// is assumed. See RFC 3986 for more details on URI syntax.
  ///
  CHAR16                        *Url;
} EFI_HTTP_REQUEST_DATA;

///
/// EFI_HTTP_RESPONSE_DATA
///
typedef struct {
  ///
  /// Response status code returned by the remote host.
  ///
  EFI_HTTP_STATUS_CODE          StatusCode;
} EFI_HTTP_RESPONSE_DATA;
*/



