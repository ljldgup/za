@Comment("�ȼ�����")
@Schema(description = "�ȼ�����")
@Column(length=255)
private String name;

@Comment("�����ȼ�")
@Schema(description = "�����ȼ�")
@Column(length=32)
private String Level;

@Comment("�ȼ���ɫ")
@Schema(description = "�ȼ���ɫ")
@Column
private String color;

@Comment("��ɫ��ʾ��ʽ���ֵ�")
@Schema(description = "��ɫ��ʾ��ʽ���ֵ�")
@Column(length=2)
private String displayType;

@Comment("����")
@Schema(description = "����")
@Column
private String description;

