/*

In all cases, any caller allocated memory must be freed by the caller (driver),
and any callee allocated memory must be freed by the callee (platform). For any HP_REST_CONFIG_OPERATION,
unused members of the EFI_HP_REST_CONFIG_BLK structure will be set to a pre-defined
default value.

*/

//*******************************************************
//HP_REST_CONFIG_OPERATION
//*******************************************************
typedef enum{
  ///
  /// Upon return from Query(), this operation asks the driver to consume the resource
  /// identified by the string given in "ResourceUri" and whose content is given
  /// in "ResourceIn". The platform will provide "ResourceIn" using AllocatePool().
  /// The driver must NOT call Free() on this buffer. "ResourceIn" will be freed
  /// by the platform. The driver may call AllocateCopyPool() if it needs to use
  /// the resource after it calls Response(). The exact same conditions apply to "ResourceUri".
  /// Upon a call to Response(), the platform will not inspect "ResourceOut" for this
  /// operation, the driver must set it NULL. The driver must write the result
  /// of the consume operation in "OperationResult".
  ///
  HpRestConsumeResourceOperation;
  ///
  /// Upon return from Query(), this operation asks the driver to produce the resource
  /// identified by the string given in "ResourceUri". "ResourceIn" is not used for
  /// this operation, the platform will always set "ResourceIn" to null for this
  /// operation. The driver must provide the requested resource in "ResourceOut"
  /// upon a call to Response(). The driver must write the result of the produce
  /// operation in "OperationResult". The platform will never attempt to modify
  /// or free "ResourceOut" directly but it may use AllocateCopyPool() to
  //  retain a copy of the resource for later use.
  ///
  HpRestProduceResourceOperation;
} HP_REST_CONFIG_OPERATION;

//*******************************************************
//EFI_HP_REST_CONFIG_BLK
//*******************************************************
typedef struct {
  ///
  /// Specifies operation being requested by the platform from the driver.
  /// Set by the platform when Query() returns. This member is only set by the platform and should never be set by the driver.
  ///
  CONST HP_REST_CONFIG_OPERATION Operation;
  ///
  /// A null terminated string containing a URI that identifies the resource on which "Operation" is performed. URI's are defined by https://tools.ietf.org/html/rfc3986.
  /// Set by the platform when Query() returns. This member is only set by the platform and should never be set or freed by the driver.
  ///
  CONST EFI_STRING               ResourceUri;
  ///
  /// If Operation== HpRestConsumeResourceOperation, ResourceIn will point to a null terminated string containing a JSON resource. JSON is defined by https://www.ietf.org/rfc/rfc4627.txt
  /// Set by the platform when Query() returns. This member is only set by the platform and should never be set or freed by the driver. If Operation==HpRestProduceResourceOperation, the platform will set this member to null.
  ///
  CONST EFI_STRING               ResourceIn;
  ///
  /// If Operation==HpRestProduceResourceOperation when Query() returns, the driver must point ResourceOut to a null terminated string containing a the JSON resource identified by ResourceUri. JSON is defined by https://www.ietf.org/rfc/rfc4627.txt
  /// Set by the driver before it calls Response(). This member is set by the driver. The platform will never attempt to free the buffer that this member points to.   The platform will never attempt to modify or free "ResourceOut" directly but it may use AllocateCopyPool() to retain a copy of the resource for later use. If Operation==HpRestConsumeResourceOperation, the platform will set this member to null since it is unused for this operation.
  ///
  EFI_STRING                     ResourceOut;
  ///
  /// Indicates the result of the operation. This member is always initialized to EFI_SUCCESS by the platform before it returns from Query(). This member should always be set by the driver with the result of an operation before it calls Response().
  ///
  EFI_STATUS                     OperationResult;
} EFI_HP_REST_CONFIG_BLK;


#define HP_REST_EXTERNAL_PROVIDER_REGISTRATION_URI_STR  L"/" /// This the reserved URI which the platform will use to request that the driver produce its external provider registration resource.
