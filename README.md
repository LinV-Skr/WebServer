# WebServer

# TODO

* 完善WebserverInit()

## 参数说明

|               参数               |     值（加粗为默认值）      |
| :------------------------------: | :-------------------------: |
|          Port，连接端口          |          **9006**           |
|    LogWriteMode，日志写入模式    |    **Sync**<br />Async，    |
|      TrigMode，触发组合模式      | **Listen_fd**<br />Conn_fd  |
| ListenTrigMode，listenfd触发模式 |           **LT**            |
|   ConnTrigMode，connfd触发模式   |           **LT**            |
|     CloseMode，优雅关闭连接      | **Immediate**<br />GraceFul |
|  SqlThreadNum，数据库连接池数量  |            **8**            |
|      ThreadNum，线程池数量       |            **8**            |
|     LogStatus，是否关闭日志      |     **Open**<br />Close     |
|     ActorModel，并发模型选择     |        **ProActor**         |
|     DataBaseName，数据库名称     |        **WebServer**        |
|  DataBaseUserName，数据库用户名  |          **root**           |
|   DataBaseUserPwd，数据库密码    |          **root**           |