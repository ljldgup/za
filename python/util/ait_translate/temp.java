@Comment("����Ӧ��id")
@Schema(description = "����Ӧ��id")
@Column(length=64)
private String clientId;

@Comment("��Ʒid")
@Schema(description = "��Ʒid")
@Column
private Long productId;

@Comment("���Ķ���id(��Ʒ�����飬��id)")
@Schema(description = "���Ķ���id(��Ʒ�����飬��id)")
@Column
private String deviceId;

@Comment("������������")
@Schema(description = "������������")
@Column(length=64)
private String dataType;

@Comment("id")
@Schema(description = "id")
@Column(length=64)
private String id;

