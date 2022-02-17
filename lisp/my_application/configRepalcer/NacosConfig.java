package com.agioe.atm.domain.common.nacos;

import com.alibaba.nacos.api.config.annotation.NacosValue;
import org.springframework.stereotype.Component;

/**
 * 配置文件读取（nacos）---全部参数
 * topic消息未找到合适的方式，先不修改
 *
 * @author zhye
 * @since 2019/10/24
 */
@Component
public class NacosConfig {
    @NacosValue(value = "${OrganizationCode}", autoRefreshed = true)
    public String organizationCode;

    /**
     * 数据查询时判断超时时间，毫秒
     */
    @NacosValue(value = "${monitoring.alarm.data.collect.overTime}", autoRefreshed = true)
    public long collectOverTime;

    /**
     * 邮箱服务配置---邮箱地址
     */
    @NacosValue(value = "${mail.fromMail.addr}", autoRefreshed = true)
    public String fromMailAddr;

    /**
     * 短信服务配置---IP地址
     */
    @NacosValue(value = "${sms.device.ip}", autoRefreshed = true)
    public String smsDeviceIp;

    /**
     * 短信服务配置---端口
     */
    @NacosValue(value = "${sms.device.port}", autoRefreshed = true)
    public int smsDevicePort;

    @NacosValue(value = "${sms.notify.enabled}", autoRefreshed = true)
    public boolean smsNotifyEnabled;

    @NacosValue(value = "${email.notify.enabled}", autoRefreshed = true)
    public boolean emailNotifyEnabled;

    /**
     * 数据获取时间间隔,当前时间11秒前---11秒
     */
    @NacosValue(value = "${ori.dateTimeInterval}", autoRefreshed = true)
    public String oriDateTimeInterval;

    /**
     * 零视token
     */
    @NacosValue(value = "${ori.token}", autoRefreshed = true)
    public String oriToken;

    /**
     * timeUpload 超时数据上传（秒）
     */
    @NacosValue(value = "${ori.timeUpload}", autoRefreshed = true)
    public long oriTimeUpload;

    /**
     * 事件发送类型---1:ap发送事件信息；2：终端发送事件信息；3：ap，终端都发送事件信息
     */
    @NacosValue(value = "${ori.eventSendType}", autoRefreshed = true)
    public String oriEventSendType;

    /**
     * ap设备类型编码
     */
    @NacosValue(value = "${web.orientate.ap.dev.type}", autoRefreshed = true)
    public String webOrientateApDevType;

    /**
     * 终端设备类型编码
     */
    @NacosValue(value = "${web.orientate.terminal.dev.type}", autoRefreshed = true)
    public String webOrientateTerminalDevType;

    /**
     * 终端设备监控属性编码
     */
    @NacosValue(value = "${web.orientate.terminal.dev.property}", autoRefreshed = true)
    public String webOrientateTerminalDevProperty;

    /**
     * 截止日期，超过这个日期未上传巡更数据则认为是漏检
     */
    @NacosValue(value = "${patrol.deadhours}", autoRefreshed = true)
    public Integer patrolDeadHours;

    /**
     * 摄像头录像结束默认时间(秒)
     */
    @NacosValue(value = "${video.record.time}", autoRefreshed = true)
    public Integer videoRecordTime;

    /**
     * 刷新消息提醒
     */
    @NacosValue(value = "${video.message}", autoRefreshed = true)
    public String videoMessage;

    /**
     * 视频设备类型
     */
    @NacosValue(value = "${video.equipTypeCode}", autoRefreshed = true)
    public String videoDevType;

    /***
     * 实时状态，故障
     */
    @NacosValue(value = "${equip.status.fault}", autoRefreshed = true)
    public String equipStatusFault;
    /***
     * 实时状态，报警
     */
    @NacosValue(value = "${equip.status.alarm}", autoRefreshed = true)
    public String equipStatusAlarm;
    /***
     * 实时状态，数据超时
     */
    @NacosValue(value = "${equip.status.overtime}", autoRefreshed = true)
    public String equipStatusOvertime;
    /***
     * 实时状态，使能禁止
     */
    @NacosValue(value = "${equip.status.disable}", autoRefreshed = true)
    public String equipStatusDisable;
    /***
     * 实时状态，无数据
     */
    @NacosValue(value = "${equip.status.nodata}", autoRefreshed = true)
    public String equipStatusNodata;
    /***
     * 实时状态，正常
     */
    @NacosValue(value = "${equip.status.normal}", autoRefreshed = true)
    public String equipStatusNormal;

    /**
     * 是否上传监控报告
     */
    @NacosValue("${monitoring.report.enable:true}")
    public Boolean reportEnable;

    /**
     * 文件服务器上传地址
     */
    @NacosValue(value = "${file.server.upload.url}",autoRefreshed = true)
    public String fileServerUploadUrl;

    /**
     * 文件服务器删除地址
     */
    @NacosValue(value = "${file.server.delete.url}",autoRefreshed = true)
    public String fileServerDeleteUrl;

    /**
     * 文件服务器对应appKey
     */
    @NacosValue(value = "${file.server.appKey}",autoRefreshed = true)
    public String fileServerAppKey;

    /**
     * 文件服务器对应appToken
     */
    @NacosValue(value = "${file.server.appToken}",autoRefreshed = true)
    public String fileServerAppToken;
}
