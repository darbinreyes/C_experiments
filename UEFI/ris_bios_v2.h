/*

First step in decoupling RisBiosProviderDxe.inf from HiiJsonTranslatorDxe.inf.

The goal of the decoupling is to make RisBiosProviderDxe.inf generic enough
to implement both BIOS provider and SA provider with the same code.

*/

// Function that gets JSON



/**

  Produces the JSON for this resource.

TODO:
What do we do if?
1. We can't read single attribute for some reason. e.g. SysConfigLibGet("AdminName") returns EFI_NOT_FOUND.

  @param[in]  This              Points to this instance of EFI_JSON_RESOURCE_PROTOCOL.
  @param[out] Json              The returned JSON if successful. NULL otherwise.

  @retval EFI_SUCCESS           JSON Successfully returned.
  @retval EFI_INVALID_PARAMETER This or Json is NULL.
  @retval EFI_PROTOCOL_ERROR    Error, JSON could not be returned. Json is set to NULL.
  @retval EFI_OUT_OF_RESOURCES  Out of memory, JSON could not be returned. Json is set to NULL.

**/
EFI_STATUS
EFIAPI
ProduceJson (
  IN  CONST EFI_JSON_RESOURCE_PROTOCOL     *This,
  OUT       json_t                         **Json
  );


typedef
EFI_STATUS
(EFIAPI * PRODUCE_JSON)(
  IN  CONST EFI_JSON_RESOURCE_PROTOCOL     *This,
  OUT       json_t                         **Json
  );

// Function that sets JSON

/**

  Consumes an instance of this resource.

TODO:
1. Define what consume means.
2. Problem, today a consume() also takes as input a client etag and consume time-stamp. These are echoed in the ProduceCC() JSON.

What do we do if?
1. We can't write single attribute for some reason.
!!2. A reset is required after consuming this resource. How will this be signaled and who does the actual reset?

  @param[in]  This              Points to this instance of EFI_JSON_CONFIG_PROTOCOL.
  @param[in]  Json              The JSON to consume.

  @retval EFI_SUCCESS           JSON consumed successfully returned.
  @retval EFI_INVALID_PARAMETER This or Json is NULL.
  @retval EFI_PROTOCOL_ERROR    Error, JSON could not be consumed. e.g. it was not valid JSON.
  @retval EFI_OUT_OF_RESOURCES  Out of memory, JSON could not be consumed.
  @retval EFI_UNSUPPORTED       This resource is not consumable.

**/
EFI_STATUS
EFIAPI
ConsumeJson(
  IN  CONST EFI_JSON_RESOURCE_PROTOCOL     *This,
  IN  CONST json_t                         *Json
  );

typedef
EFI_STATUS
(EFIAPI * CONSUME_JSON)(
  IN  CONST EFI_JSON_RESOURCE_PROTOCOL     *This,
  IN        json_t                         *Json
  );

// forward decl.
#define _EFI_JSON_RESOURCE_PROTOCOL EFI_JSON_RESOURCE_PROTOCOL;

struct _EFI_JSON_RESOURCE_PROTOCOL {
/// All resources are producible.
PRODUCE_JSON  ProduceJson;
/// Some resources are only producible while others are both producible and consumable.
/// Calling this function on a resource that is not consumable is a NO-OP, and EFI_UNSUPPORTED will be returned.
CONSUME_JSON  ConsumeJson;
};


/*

Idea:

Every resource of the provider will get an instance of this protocol
associated with it.

Thus, if I want to produce the resource, I can get the EFI_JSON_RESOURCE_PROTOCOL
instance tied to that resource, then call

Status=This->Produce(This, &Json);

Similarly, to Consume a resource.

Each individual Consume/Produce pair will be implemented in its own .c/.h, somewhat
like we do today, e.g. BootOrder.c/h. Directories can be used to organize resource
files into groups, e.g. JsonResourceDxe/BootOrder/BootOrder.c.h

If we place the function pointers in a table along with an EFI_HANDLE on which
to install the json resource protocol instance, then why not simply
have a table without any handles/protocol installations?


-try to think about the interface with RisBiosDxe.inf.

We will define and reserve a fixed resource suburi which will be used to identify
the Produce()/Consume() function pair for the External Provider's registration
JSON. This resource is only producible, not consumable.

#define PROVIDER_REGISTRATION_SUBURI L"/Providers"


Calling the Produce() function of the "/Providers" resource will return the
provider's registration JSON.

The resource producer is the client of the external provider service.

The resource producer(external provider service client) will use the Produce()/Consume() functions as described
above indirectly, via an HTTP-like interface in which HTTP GETs to a resource
identified by its sub-uri will map to a Produce() call for that resource.

Similarly HTTP PUTs will map to a Consume() call for the specified resource.


-ALL RESOURCES MUST HAVE AN ETAG. REGISTRATION UPDATES AND SCHEMA/REGISTRY publishing.
ALL such HTTP gets are required to return an Etag. This is especially important
for the /Providers resource, whose Etag will be used to determine if a provider
registration update is required (as opposed to first time registration). If an external
provider carries schema/registry files which need to be published by the platform
on behalf the external provider, the registration's Etag must be different from
the Etag of a previous registration. The platform will only request the provider's
schema and registry files upon initial registration or upon a registration update.
Again, all resources, including schemas and registry files should, have a Etag
associated with it.


-WHEN THE PROVIDER IS ALREADY REGISTERED, WHAT HAPPENS.
If neither an initial registration or registration update
is necessary on a particular boot of the platform, then the platform will
only request the registration JSON to be produced for the purpose of ETag comparison
with the provider's current registration. The platform will use the returned registration
JSON to create the provider's Keep-Alive JSON in order to keep the provider's
resources from being garbage collected (see RIS spec).


-ASSUMPTION/PRECONDITION:
Any change in a providers schema or registry metadata files will result
in a change to the providers registration ETag. This is because the provider
registration Etag is a hash of the registration json itself, and that JSON will
change as a result of a schema-type/registry-type version change (version string of the
type will be different). In addition to being used by the platform (external provider service)
to determine if a registration update is necessary (e.g. a new resource was added),
this Etag will be used to determine if the platform should re-publish the driver's (resource provider)
schema/registry files to the RIS service.

-ASSUMPTION/PRECONDITION:
The provider's registration JSON can be used to compute unique sub-uris for each
resource, schema, and registry. This sub-uris will be used by the resource provider
to direct GETs/PUTs (produce/consume) requests operations to an individual resource.


// Genius idea: once we implement RIS P2D interface we can re-use the same code
// for the resource provider produce()/consume() interface.

Outside of a provider's resources and associated Etags, all other data can be
communicated via HTTP headers, either standard or defined by us.


-NOTE: try to
-see if using events like in EFI_HTTP_TOKEN would be useful in this design.
-Don’t waste time making design descriptions pretty looking at this stage. Focus
-on content not formatting of documentation like a state machine diagram.


*/