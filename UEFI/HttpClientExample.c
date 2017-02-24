
/*
UEFI Spec. v2.5 Section 28.6.2.1

Usage Examples Here is an example of a client making a HTTP Request to
download a driver bundle from Intel Driver Download Center. This example
includes sample code for how to support a client that is behind a HTTP proxy
server.

*/


#include <Uefi.h>
#include <HttpProtocol.h>
BOOLEAN gRequestCallbackComplete; // since these are implicitly external static variables they are initialized to false.
BOOLEAN gResponseCallbackComplete;

VOID
EFIAPI
RequestCallback(
  IN  EFI_EVENT   Event,
  IN  VOID        *Context
  )
{
  gRequestCallbackComplete = TRUE;
}

VOID
EFIAPI
ResponseCallback(
  IN  EFI_EVENT   Event,
  IN  VOID        *Context
  )
{
  gResponseCallbackComplete = TRUE;
}

EFI_STATUS
EFIAPI
HttpClientMain(
  IN  EFI_HANDLE        ImageHandle,
  IN  EFI_SYSTEM_TABLE  *SystemTable
  )
{
  EFI_STATUS                    Status;

  EFI_SERVICE_BINDING_PROTOCOL  *ServiceBinding; // der-dbg: Protocol stuff
  EFI_HANDLE                    *Handle;
  EFI_HTTP_PROTOCOL             *HttpProtocol;

  EFI_HTTP_CONFIG_DATA          ConfigData;  // der-dbg: HTTP config stuff
  EFI_HTTPv4_ACCESS_POINT       IPv4Node;

  EFI_HTTP_REQUEST_DATA         RequestData;  // der-dbg: HTTP request stuff
  EFI_HTTP_HEADER               RequestHeader;
  EFI_HTTP_MESSAGE              RequestMessage;
  EFI_HTTP_TOKEN                RequestToken;

  EFI_HTTP_RESPONSE_DATA        ResponseData; // der-dbg: HTTP response stuff.
  EFI_HTTP_MESSAGE              ResponseMessage;
  EFI_HTTP_TOKEN                ResponseToken;

  UINT8                         Buffer[0x100000]; // der-dbg: body buffer // == 2^20 == 1 MB == 1,048,576

  EFI_TIME                      Baseline; // der-dbg: Timer stuff
  EFI_TIME                      Current;
  UINTN                         Timer;

  UINTN                         Index; // der-dbg: body buffer stuff.
  UINTN                         ContentDownloaded;
  UINTN                         ContentLength;


  Status = gBS->LocateProtocol(
                  &gEfiHttpServiceBindingProtocolGuid,
                  NULL,
                  &ServiceBinding
                  );
  // TODO: Handle error...

  Status = ServiceBinding->CreateChild(ServiceBinding, &Handle);
  // TODO: Handle error...

  Status = gBS->HandleProtocol(Handle, &gEfiHttpProtocolGuid, &HttpProtocol);
    // TODO: Handle error...

  ConfigData.HttpVersion = HttpVersion11;
  ConfigData.TimeOutMillisec = 0; // Indicates default timeout period
  ConfigData.LocalAddressIsIPv6 = FALSE;

  ZeroMem(&IPv4Node, sizeof(IPv4Node));
  IPv4Node.UseDefaultAddress = TRUE; // Obtain IP address from DHCP
  ConfigData.AccessPoint.IPv4Node = &IPv4Node;

  // The HTTP driver must first be configured before requests or responses can
  // be processed. This is the same for other network protocols such as TCP.
  Status = HttpProtocol->Configure(HttpProtocol, &ConfigData);

  // This request message is initialized to request a sample driver bundle
  // from Intel's driver download center. To download a file, we use HTTP GET.
  RequestData.Method = HttpMethodGet;

  // URI where the file is located that we want to download. // der-dbg: For some reason they made the Url CHAR16 but the Headers CHAR8
  RequestData.Url = L"http://downloadmirror.intel.com/23418/a08/FYKH-Win8.1-64bit-Driver- Bundle-Sep2014.zip";

  // This header tells the HTTP driver to relay the HTTP request
  // via a proxy server. This header is just used to demonstrate
  // how to relay through a proxy with this driver. The method
  // for obtaining the proxy address is up to the client. The
  // HTTP driver does NOT resolve this on its own.

  RequestHeader.FieldName = "Host";
  RequestHeader.FieldValue = "my.proxyserver.com";

  // Message format just contains a pointer to the request data
  // and body info, if applicable. In the case of HTTP GET, body
  // is not relevant.
  RequestMessage.Data.Request = &RequestData;

  // Just one header being provided in the HTTP message.
  RequestMessage.HeaderCount = 1;
  RequestMessage.Headers = &RequestHeader;
  RequestMessage.BodyLength = 0;
  RequestMessage.Body = NULL;
  // Token format is similar to the token format in EFI TCP protocol.

  RequestToken.Event = NULL;

  Status = gBS->CreateEvent(
                  EVT_NOTIFY_SIGNAL,
                  TPL_CALLBACK,
                  RequestCallback,
                  NULL,
                  &RequestToken.Event
                  );

  // TODO: Handle error...

  RequestToken.Status = EFI_SUCCESS;
  RequestToken.Message = &RequestMessage;

  gRequestCallbackComplete = FALSE;

  // Finally, make HTTP request.
  Status = HttpProtocol->Request(HttpProtocol, &RequestToken);
  // TODO: Handle error...

  Status = gRT->GetTime(&Baseline, NULL);

  // TODO: Handle error...
  // Optionally, wait for a certain amount of time before cancelling
  // the request. In this case, we'll allow the network stack 10
  // seconds to send the request successfully.

  for (Timer = 0; !gRequestCallbackComplete && Timer < 10; ) { // der-dbg:  This is basically polling for the response to be sent.
    // Give the HTTP driver some motivation...
    HttpProtocol->Poll(HttpProtocol);

    // In practice, a call to GetTime() only fails when the total
    // elapsed time between the last call to to GetTime() is less
    // than the resolution of one tick (e.g. 1 second, depending
    // on capabilities of hardware). We only care to check the time
    // when the call succeeds.
    if (!EFI_ERROR(gRT->GetTime(&Current, NULL)) && Current.Second != Baseline.Second)
    {
        // One second has passed, so update Current time and
        // increment the counter.
        Current = Baseline;
        ++Timer;
    }
  } // for

  // Cancel request if we did not get a notification from the HTTP
  // driver in a timely manner.

  if (!gRequestCallbackComplete) {
    Status = HttpProtocol->Cancel(HttpProtocol, &RequestToken);
    // TODO: Handle error and exit condition...
  }

  // Assuming we succeed in our request... // der-dbg: At this point we know the request was sent so we can focus on getting the response.

  // This response message is different than request in that the
  // HTTP driver is responsible for allocating the headers during
  // a response instead of the caller.
  ResponseData.StatusCode = HTTP_STATUS_UNSUPPORTED_STATUS;
  ResponseMessage.Data.Response = &ResponseData;

  // HeaderCount will be updated by the HTTP driver on response.
  ResponseMessage.HeaderCount = 0;

  // Headers will be populated by the driver on response.
  ResponseMessage.Headers = NULL;

  // BodyLength maximum limit is defined by the caller. On response,
  // the HTTP driver will update BodyLength to the total number of
  // bytes copied to Body. This number will never exceed the initial
  // maximum provided by the caller.
  ResponseMessage.BodyLength = sizeof(Buffer);
  ResponseMessage.Body       = Buffer;

  // Token format is similar to the token format in EFI TCP protocol.
  ResponseToken.Event = NULL;
  Status = gBS->CreateEvent(
                  EVT_NOTIFY_SIGNAL,
                  TPL_CALLBACK,
                  NULL,
                  &ResponseToken,
                  &ResponseToken.Event
                  );

  ResponseToken.Status = EFI_SUCCESS;
  ResponseToken.Message = &ResponseMessage;

  gResponseCallbackComplete = FALSE;

  // Finally, make HTTP request.
  Status = HttpProtocol->Response(HttpProtocol, &ResponseToken);
  // TODO: Handle error...

  Status = gRT->GetTime(&Baseline, NULL);
  // TODO: Handle error...
  // Optionally, wait for a certain amount of time before cancelling.
  for (Timer = 0; !gResponseCallbackComplete && Timer < 10; ) { // der-dbg: Now we poll for the response.

    HttpProtocol->Poll(HttpProtocol);

    if (!EFI_ERROR(gRT->GetTime(&Current, NULL)) && Current.Second != Baseline.Second)
    {
        // One second has passed, so update Current time and
        // increment the counter.
        Current = Baseline;
        ++Timer;
    }
  }

  // Remove response token from queue if we did not get a notification
  // from the remote host in a timely manner.
  if (!gResponseCallbackComplete) {
    Status = HttpProtocol->Cancel(HttpProtocol,&ResponseToken);
    // TODO: Handle error and exit condition...
  }

  // Assuming we successfully received a response...
  for (Index = 0; Index < ResponseMessage.HeaderCount; ++Index) { // der-dbg: At this point we have a response, the first thing we do is get the total body size from the ContentLength header.
    // We can parse the length of the file from the ContentLength header.
    if (!AsciiStriCmp(ResponseMessage.Headers[Index].FieldName,"ContentLength")) {
        ContentLength = AsciiStrDecimalToUintn(ResponseMessage.Headers[Index].FieldValue);
      }
  }

  ContentDownloaded = ResponseMessage.BodyLength;
  // TODO:
  // Downloaded data exists in Buffer[0..ResponseMessage.BodyLength]. // der-dbg: WRONG!  ResponseMessage.BodyLength-1 should be contain the last byte of the body, biatch. Assuming is was smaller or equal in size to the buffer you provided on the initial call to Response().
  // At this point, depending on business use case, the content can
  // be written to a file, stored on the heap, etc.


  while (ContentDownloaded < ContentLength) { // der-dbg: This is chunking very similar to what we do in our BlobStoreDxe.inf.

    // If we make it here, we haven't yet downloaded the whole file and
    // need to keep going.
    ResponseMessage.Data.Response = NULL;
    if (ResponseMessage.Headers != NULL) {
      // No sense hanging onto this anymore.
      FreePool(ResponseMessage.Headers);  // der-dbg:  IMPORTANT! Note that you don't need to FreePool() the header name/values, just the containing struct, they must be freed by the driver at some point later.
    }

    ResponseMessage.HeaderCount = 0;
    ResponseMessage.BodyLength = sizeof(Buffer);
    ZeroMem(Buffer, sizeof(Buffer)); // der-dbg:  Note this example does not explicitly save the part of the body we already received.

    // ResponseMessage.Body still points to Buffer.
    gResponseCallbackComplete = FALSE;

    // The HTTP driver accepts a token where Data, Headers, and
    // HeaderCount are all 0 or NULL. The driver will wait for a
    // response from the last remote host which a transaction occurred
    // and copy the response directly into Body, updating BodyLength
    // with the total amount copied (downloaded).
    Status = HttpProtocol->Response(HttpProtocol, &ResponseToken); // TODO: Handle error...  // der-dbg: Here's where get the next chunk.

    Status = gRT->GetTime(&Baseline, NULL);
    // TODO: Handle error...

    // Optionally, wait for a certain amount of time before canceling.
    for (Timer = 0; !gResponseCallbackComplete && Timer < 10; ) {

      HttpProtocol->Poll(HttpProtocol);

      if (!EFI_ERROR(gRT->GetTime(&Current, NULL)) && Current.Second != Baseline.Second)
      {
        // One second has passed, so update Current time and
        // increment the counter.
        Current = Baseline;
        ++Timer;
      }
    }

    // Remove response token from queue if we did not get a notification
    // from the remote host in a timely manner.
    if (!gResponseCallbackComplete) {
      Status = HttpProtocol->Cancel(HttpProtocol, &ResponseToken);
      // TODO: Handle error and exit condition...
    }
    // Assuming we successfully received a response...
    ContentDownloaded += ResponseMessage.BodyLength;

    // TODO:
    // Downloaded data exists in Buffer[0..ResponseMessage.BodyLength].
    // Append data to a file, heap memory, etc. // der-dbg: Here's where we would be appending the part of the body we received to a file.

  } // while

  // Perform any necessary cleanup and handling of downloaded file
  // assuming we succeeded at downloading the content. Depending on
  // where the data was stored as per business need, that data can // be consumed at this point. For example, if the data was stored // to a file system, the file can be opened and consumed.
  return EFI_SUCCESS;
} // main