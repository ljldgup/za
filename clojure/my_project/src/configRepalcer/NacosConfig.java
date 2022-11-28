package com.agioe.atm.domain.monitoring.alarm.util;

import com.alibaba.nacos.api.config.annotation.NacosValue;
import org.springframework.beans.factory.annotation.Value;
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
    /**
     * 组织编码
     */
    @NacosValue(value = "${OrganizationCode}", autoRefreshed = true)
    public String organizationCode;

    /**
     * 事件稀疏-开关
     */
    @NacosValue(value = "${monitoring.alarm.eventWave.enable}", autoRefreshed = true)
    public Boolean eventWaveEnable;

    /**
     * 事件稀疏-值参数
     */
    @NacosValue(value = "${monitoring.alarm.eventWave.val}", autoRefreshed = true)
    public float eventWaveVal;

    /**
     * 事件参数（单位 毫秒）
     */
    @NacosValue(value = "${monitoring.alarm.eventWave.time}", autoRefreshed = true)
    public long eventWaveTime;

    /**
     * 提示类事件自动存入历史 注意此处的配置是反的，即此处配置的事件类别的事件存实时，而没配的存入历史
     */
    @NacosValue(value = "${monitoring.alarm.event.autoToHistory}", autoRefreshed = true)
    public String autoToHistory;

    /**
     * 数据采集周期 毫秒
     */
    @NacosValue(value = "${monitoring.alarm.data.collect.period}", autoRefreshed = true)
    public long collectPeriod;

    /**
     * 没有数据波动时数据存储间隔，毫秒
     */
    @NacosValue(value = "${monitoring.alarm.data.collect.noDataPeriod}", autoRefreshed = true)
    public long noDataPeriod;

    /**
     * 数据查询时判断超时时间，毫秒
     */
    @NacosValue(value = "${monitoring.alarm.data.collect.overTime}", autoRefreshed = true)
    public long collectOverTime;

    /**
     * 特殊设备类型的超时时间配置，格式必须是：设备类型1,时间1,设备类型2,时间2,...,设备类型n,时间n
     */
    @NacosValue(value = "${monitoring.alarm.data.collect.specialOverTimes:}", autoRefreshed = true)
    public String specialOverTimes;

    /**
     * 曲线点数上限
     */
    @NacosValue(value = "${monitoring.alarm.history.curve.numLimitUp}", autoRefreshed = true)
    public long numLimitUp;

    /**
     * 本地控制判断范围 单位毫秒
     */
    @NacosValue(value = "${monitoring.alarm.control.localControl}", autoRefreshed = true)
    public long localControl;

    /**
     * 是否开启自动处理
     */
    @NacosValue(value = "${monitoring.alarm.isAutoProcess}", autoRefreshed = true)
    public int isAutoProcess;

    /**
     * 自动处理：优先关闭的事件等级
     */
    @NacosValue(value = "${monitoring.alarm.autoProcessLevel}", autoRefreshed = true)
    public String autoProcessLevel;

    /**
     * 自动处理：向前推该天数为 需处理的事件发生截止日期
     */
    @NacosValue(value = "${monitoring.alarm.autoProcessDay}", autoRefreshed = true)
    public int autoProcessDay;

    /**
     * 自动处理：实时事件表中事件总数上限
     */
    @NacosValue(value = "${monitoring.alarm.autoProcessLimit}", autoRefreshed = true)
    public long autoProcessLimit;

    /**
     * 撤防状态的设备，可以产生的事件对应的事件码
     */
    @NacosValue(value = "${monitoring.alarm.disarmedEventCodes}", autoRefreshed = true)
    public String disarmedEventCodes;

    /**
     * 推送功能开关
     */
    @NacosValue(value = "${monitoring.alarm.push.enable}", autoRefreshed = true)
    public Boolean pushEnable;

    /**
     * 风险评估
     */
    @NacosValue(value = "${monitoring.alarm.risk.enable}", autoRefreshed = true)
    public Boolean riskEnable;

    /***
     * redis实时数据缓存初始化时，查询点号数据时间范围（当前时间向前推），单位小时
     */
    @NacosValue(value = "${monitoring.alarm.redis.init.timeBefore}", autoRefreshed = true)
    public int redisInitTimeBefore;

    /**
     * 电缆监测菜单树编码
     */
    @NacosValue(value = "${cable.monitor.menu.tree.code}",autoRefreshed = true)
    public String cableMonitorMenuTreeCode;

    @NacosValue(value = "${atm.bigDataLog.open:true}",autoRefreshed = true)
    public Boolean bigDataLogOpen;

    /**
     * 电缆监测 相位度数页面展示时度数合并参考值
     */
    @NacosValue(value = "${cable.monitor.phaseDegreeMerge.size:1}",autoRefreshed = true)
    public int phaseDegreeMergeSize;

    //机器人相关开始
    /**
     * 是否初始化机器人客户端
     */
    @NacosValue(value = "${init.robot.client}",autoRefreshed = true)
    public Boolean initRobotClient;

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
     * 机器人视频数据保存天数
     */
    @NacosValue(value = "${robot.his.video.keep.time}",autoRefreshed = true)
    public Integer robotHisVideoKeepTime;

    /**
     * 文件服务器对应appKey
     */
    @NacosValue(value = "${file.server.appKey}",autoRefreshed = true)
    public String robotFileServerAppKey;

    /**
     * 文件服务器对应appToken
     */
    @NacosValue(value = "${file.server.appToken}",autoRefreshed = true)
    public String robotFileServerAppToken;

    /**
     * 机器人实时数据超时时间(单位毫秒)
     */
    @NacosValue(value = "${robot.realTime.data.overTime}",autoRefreshed = true)
    public Long robotRealTimeDataOverTime;

    /**
     * 机器人设备类型编码
     */
    @NacosValue(value = "${equip.type.robot}",autoRefreshed = true)
    public String equipTypeRobot;

    /**
     * 机器人树节点类型
     */
    @NacosValue(value = "${tree.node.type.tunnel}",autoRefreshed = true)
    public String treeNodeTypeTunnel;

    /**
     * 系统级联关系类型编号
     */
    @NacosValue(value = "${tree.type.code.robot}",autoRefreshed = true)
    public String treeTypeCodeRobot;

    /**
     * 机器人联动轮询周期
     */
    @NacosValue(value = "${robot.linkage.schedule}",autoRefreshed = true)
    public Integer robotLinkageSchedule;

    /**
     * 机器人联动轮询超时时间
     */
    @NacosValue(value = "${robot.linkage.query.time}",autoRefreshed = true)
    public Integer robotLinkageQueryTime;

    /**
     * 机器人联动确认报警超时时间
     */
    @NacosValue(value = "${robot.linkage.confirm.time}",autoRefreshed = true)
    public Integer robotLinkageConfirmTime;

    /**
     * 机器人图片下载次数
     */
    @NacosValue(value = "${robot.img.download.times}",autoRefreshed = true)
    public Integer robotImgDownLoadTimes;

    /**
     * 机器人视频下载次数
     */
    @NacosValue(value = "${robot.video.download.times}",autoRefreshed = true)
    public Integer robotVideoDownLoadTimes;

    /**
     * 机器人全程录像下载次数
     */
    @NacosValue(value = "${robot.whole.video.download.times}",autoRefreshed = true)
    public Integer robotWholeVideoDownLoadTimes;

    /**
     * 机器人定时轮训滞后时间,单位min
     */
    @NacosValue(value = "${robot.his.data.query.delay.time}",autoRefreshed = true)
    public Integer robotHisDataQueryDelayTime;

    /**
     * 数据权限开关
     */
    @NacosValue(value="${data.role.active}",autoRefreshed = true)
    public Boolean dataRoleActive;

    /**
     * 最大放电量计算时，放电量由大到小排序后，忽略的数据的比例
     */
    @NacosValue(value="${cable.maxQ.ignore.ratio:0.05}",autoRefreshed = true)
    public Double maxQIgnoreRatio;


    /**
     * 是否启用通知详细的事件描述信息
     */
    @NacosValue(value="${notify.full.desc.enable:false}",autoRefreshed = true)
    public Boolean notifyFullDescEnable;
}
