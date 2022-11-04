@Comment("权限名称")
@Schema(description = "权限名称")
@Column(length=255)
private String "name";

@Comment("说明")
@Schema(description = "说明")
@Column(length=255)
private String "describe";

@Comment("id")
@Schema(description = "id")
@Column(length=64)
private String id;

@Comment("存储方式")
@Schema(description = "存储方式")
@Column
private String storageType;

@Comment("存储时间")
@Schema(description = "存储时间")
@Column
private Long storageTime;

@Comment("清理方式")
@Schema(description = "清理方式")
@Column
private String cleanType;

@Comment("是否稀疏")
@Schema(description = "是否稀疏")
@Column
private Boolean sparse;

@Comment("间隔数量")
@Schema(description = "间隔数量")
@Column
private Long interval;

