@Comment("Ȩ������")
@Schema(description = "Ȩ������")
@Column(length=255)
private String "name";

@Comment("˵��")
@Schema(description = "˵��")
@Column(length=255)
private String "describe";

@Comment("id")
@Schema(description = "id")
@Column(length=64)
private String id;

@Comment("�洢��ʽ")
@Schema(description = "�洢��ʽ")
@Column
private String storageType;

@Comment("�洢ʱ��")
@Schema(description = "�洢ʱ��")
@Column
private Long storageTime;

@Comment("����ʽ")
@Schema(description = "����ʽ")
@Column
private String cleanType;

@Comment("�Ƿ�ϡ��")
@Schema(description = "�Ƿ�ϡ��")
@Column
private Boolean sparse;

@Comment("�������")
@Schema(description = "�������")
@Column
private Long interval;

