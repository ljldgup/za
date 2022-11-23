@Comment("等级名称")
@Schema(description = "等级名称")
@Column(length=255)
private String name;

@Comment("报警等级")
@Schema(description = "报警等级")
@Column(length=32)
private String Level;

@Comment("等级颜色")
@Schema(description = "等级颜色")
@Column
private String color;

@Comment("颜色显示方式，字典")
@Schema(description = "颜色显示方式，字典")
@Column(length=2)
private String displayType;

@Comment("描述")
@Schema(description = "描述")
@Column
private String description;

