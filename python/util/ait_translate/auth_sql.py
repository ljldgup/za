import random

if __name__ == '__main__':
    sql = "INSERT INTO public.s_autz_setting_info " \
          "(data_accesses,dimension_type_name,dimension_type,dimension_target,dimension_target_name,\"merge\",permission,id,state,priority,actions)" \
          " VALUES " \
          "(NULL,\'用户\',\'user\',\'{}\',\'{}\',true,\'{}\',\'{}\',1,10,\'[\"query\",\"save\",\"delete\"]\');"
    permissions = ["resource_space","northapp","subuser-user-manager","zidingyi-openapi","device-alarm","rule-model","geo-manager",
             "device-msg-task","system-logger","zidingyi-openapi2","protocol-supports","network-simulator","dashboard","tenant-side-manager",
             "organization","firmware-manager","device-opt-api","file","tenant-manager","device-group","rule-scene","network-config",
             "access-logger","permission","device-category","device-api","wechatMessage","menu","assets-bind","test99","visualization-component",
             "notifier","device-instance","certificate","template","device-firmware-manager","user","dictionary","autz-setting","dimension",
             "rule-instance","system-config","firmware-upgrade-task-manager","datasource-config","visualization",
             "user-token","open-api","device-api-product","device-gateway","device-product","product-model","device-batch"]
    start = 0
    userid = '1554437991744352256'

    for permission in permissions:
        print(sql.format(userid, userid, permission,
                         str(random.randint(1, 1e32))))
