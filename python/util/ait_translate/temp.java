@Comment("关联设备id:")
@Schema(description = "关联设备id")
@Column(length=64)
private String deviceId;

@Comment("配置类型:动态属性dynamicProperties，消息")
@Schema(description = "配置类型")
@Column(length=32)
private String conifgType;

@Comment("对应物模型中的标致:")
@Schema(description = "对应物模型中的标致")
@Column
private String code;

@Comment("")
@Schema(description = "")
@Column
private String parentId;

@Comment("R可读，W可写，RW读写:")
@Schema(description = "R可读，W可写，RW读写")
@Column(length=8)
private String accessMode;

@Comment("设备读取:")
@Schema(description = "设备读取")
@Column
private Boolean readable;

@Comment("起始地址:")
@Schema(description = "起始地址")
@Column
private Long beginAddress;

@Comment("地址长度:")
@Schema(description = "地址长度")
@Column
private Long addrLength;

@Comment("读功能码:")
@Schema(description = "读功能码")
@Column(length=8)
private String readFunctionCode;

@Comment("写功能码:")
@Schema(description = "写功能码")
@Column(length=8)
private String writeFunctionCode;

@Comment("操作方式:")
@Schema(description = "操作方式")
@Column(length=8)
private String accessWay;

@Comment("默认值:")
@Schema(description = "默认值")
@Column
private String defaultValue;

@Comment("")
@Schema(description = "")
@Column(length=8)
private String evaluateMethod;

