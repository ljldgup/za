import threading
from urllib import parse

from sqlalchemy import Column, String, PrimaryKeyConstraint
from sqlalchemy import create_engine
from sqlalchemy.orm import declarative_base, session, sessionmaker

from config.common_config import common_config

simulator_base = declarative_base()
database_config = common_config['database']
url = 'postgresql://{}:{}@{}:{}/{}'.format(
    database_config['username'], parse.quote_plus(database_config['password']), database_config['host'],
    database_config['port'], database_config['database'])

# 创建Session类实例
simulator_engine = create_engine(url)
session_lock = threading.Lock()
simulator_session = sessionmaker(bind=simulator_engine, autoflush=True)()
simulator_base.metadata.create_all(simulator_engine, checkfirst=True)


class GatewayChild(simulator_base):
    __tablename__ = 'gateway_children'
    gateway_id = Column(String(64))
    parent_node_id = Column(String(64))
    node_id = Column(String(64))
    product_code = Column(String(64))
    device_id = Column(String(64))
    hash = Column(String(64))
    date = Column(String(10))
    __table_args__ = (
        PrimaryKeyConstraint('hash', 'gateway_id', 'node_id', name='hash_gateway_child_idx'),
    )


def add_gateway_children(children: list):
    with session_lock:
        simulator_session.bulk_save_objects(children)
        simulator_session.commit()


def find_all_gateway_children(gateway_id: str, hash: str):
    # print(simulator_session.query(GatewayChildren).where(GatewayChildren.hash == hash).where(
    #     GatewayChildren.gateway_id == gateway_id).statement)
    with session_lock:
        result = simulator_session.query(GatewayChild).where(GatewayChild.hash == hash) \
            .where(GatewayChild.gateway_id == gateway_id).all()

    return result


simulator_base.metadata.create_all(simulator_engine, checkfirst=True)

# if __name__ == '__main__':
#     simulator_base.metadata.create_all(simulator_engine, checkfirst=True)
#     date = time.strftime('%a %b %d %H:%M:%S %Y')
#     add_gateway_children(
#         [GatewayChild(gateway_id=str(i), parent_node_id=str(i), node_id=str(i), product_code=str(i), hash=str(i),
#                       date=date)
#          for i in range(10)])
#     result = find_all_gateway_children('1', '0')
#     print(result)
