@Comment("�����豸id:")
@Schema(description = "�����豸id")
@Column(length=64)
private String deviceId;

@Comment("��������:��̬����dynamicProperties����Ϣ")
@Schema(description = "��������")
@Column(length=32)
private String conifgType;

@Comment("��Ӧ��ģ���еı���:")
@Schema(description = "��Ӧ��ģ���еı���")
@Column
private String code;

@Comment("")
@Schema(description = "")
@Column
private String parentId;

@Comment("R�ɶ���W��д��RW��д:")
@Schema(description = "R�ɶ���W��д��RW��д")
@Column(length=8)
private String accessMode;

@Comment("�豸��ȡ:")
@Schema(description = "�豸��ȡ")
@Column
private Boolean readable;

@Comment("��ʼ��ַ:")
@Schema(description = "��ʼ��ַ")
@Column
private Long beginAddress;

@Comment("��ַ����:")
@Schema(description = "��ַ����")
@Column
private Long addrLength;

@Comment("��������:")
@Schema(description = "��������")
@Column(length=8)
private String readFunctionCode;

@Comment("д������:")
@Schema(description = "д������")
@Column(length=8)
private String writeFunctionCode;

@Comment("������ʽ:")
@Schema(description = "������ʽ")
@Column(length=8)
private String accessWay;

@Comment("Ĭ��ֵ:")
@Schema(description = "Ĭ��ֵ")
@Column
private String defaultValue;

@Comment("")
@Schema(description = "")
@Column(length=8)
private String evaluateMethod;

