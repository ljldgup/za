@Comment("北向应用id")
@Schema(description = "北向应用id")
@Column(length=64)
private String clientId;

@Comment("产品id")
@Schema(description = "产品id")
@Column
private Long productId;

@Comment("订阅对象id(产品，分组，的id)")
@Schema(description = "订阅对象id(产品，分组，的id)")
@Column
private String deviceId;

@Comment("订阅数据类型")
@Schema(description = "订阅数据类型")
@Column(length=64)
private String dataType;

@Comment("id")
@Schema(description = "id")
@Column(length=64)
private String id;

