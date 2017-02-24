//*******************************************************
//EFI_HP_REST_CONFIG_BLK
//*******************************************************
typedef struct {
EFI_HTTP_MESSAGE   *Request;  // Set by the platform. Upon return from Query(0), an HTTP request message containing a configuration request. The integer argument is the "Instance" number.
EFI_HTTP_MESSAGE   *Response; // Set by the driver. Upon a call to Response(0), an HTTP response message containing the result of the configuration request provided to the driver from the platform on return from Query(0).
} EFI_HP_REST_CONFIG_BLK;

#define EFI_PLATFORM_TO_DRIVER_CONFIGURATION_HP_REST_CONFIG_GUID  {0xDEADBEEF}

STATIC CONST EFI_GUID HpRestConfigParameterTypeGuid = EFI_PLATFORM_TO_DRIVER_CONFIGURATION_HP_REST_CONFIG_GUID;


//query

EFI_STATUS
EFIAPI
GetExternalProviderRegistationQuery(
  IN CONST  EFI_PLATFORM_TO_DRIVER_CONFIGURATION_PROTOCOL *This,
  IN CONST  EFI_HANDLE  ControllerHandle,
  IN CONST  EFI_HANDLE  ChildHandle OPTIONAL,
  IN CONST  UINTN       *Instance,
  OUT       EFI_GUID    **ParameterTypeGuid,
  OUT       VOID        **ParameterBlock,
  OUT       UINTN       *ParameterBlockSize
  )
{
EFI_HP_REST_CONFIG_BLK        Block;
EFI_HTTP_REQUEST_DATA         RequestData;
EFI_HTTP_MESSAGE              Request;
EFI_HTTP_HEADER               RequestHeader;

//
// Args valid?
//
if(This == NULL || ControllerHandle == NULL || Instance == NULL || ParameterTypeGuid == NULL || ParameterBlock == NULL || ParameterBlockSize == NULL) // der-note: EFI_HANDLE is just a typedef for void *.
  return EFI_INVALID_PARAMETER;
}
// check instance valid/incremented as expected based on previous calls if any..

// if (ChildHandle == NULL ) ? then what?


//
// Init the Request part of the block
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

// Set the block request
Block.Request = &Request;

//
// Init. the Response part of the block
//

EFI_HTTP_MESSAGE              Response;
EFI_HTTP_RESPONSE_DATA        ResponseData;
UINT8                         Buffer[0x100000]; // der-dbg: body buffer // == 2^20 == 1 MB == 1,048,576

//
// The driver is responsible for allocating the headers before it calls
// Response().
//
ResponseData.StatusCode = HTTP_STATUS_UNSUPPORTED_STATUS;
Response.Data.Response = &ResponseData;

// HeaderCount will be updated by the driver on response.
Response.HeaderCount = 0;

// Headers will be populated by the driver on response.
Response.Headers = NULL;

// BodyLength maximum limit is defined by the caller. On response,
// the HTTP driver will update BodyLength to the total number of
// bytes copied to Body. This number will never exceed the initial
// maximum provided by the caller.
Response.BodyLength = sizeof(Buffer);
Response.Body       = Buffer;

// Set the block response
Block.Response = &Response;

//
// All done, just need to set the return args.
//
*ParameterTypeGuid = (EFI_GUID *)&HpRestConfigParameterTypeGuid;
*ParameterBlock = (VOID *) &Block;
*ParameterBlockSize = sizeof(Block);

Status = EFI_SUCCESS;

return Status;
}

// NEXT: specify how a request will be given in general, caller/vs callee, then do same for request. Focus on what not how. Add complexity incrementally.

