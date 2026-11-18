"""The pinned PC dialect, with bounded streaming decoders per transport."""
from .generated import finsrov as mav
mav.MAVLINK_IGNORE_CRC = 0  # Environment overrides must not disable control CRC.


class Codec:
    def __init__(self, system=1, component=1):
        self.encoder = mav.MAVLink(None, srcSystem=system, srcComponent=component)
        self.decoder = mav.MAVLink(None)
        self.decoder.robust_parsing = True

    def encode(self, kind, **fields):
        message = getattr(self.encoder, kind.lower() + '_encode')(**fields)
        data = message.pack(self.encoder)
        self.encoder.seq = (self.encoder.seq + 1) & 255
        return data

    def decode(self, data):
        return [m for m in (self.decoder.parse_buffer(data) or []) if m.get_type() != 'BAD_DATA']


def fields(message):
    result = message.to_dict()
    result.pop('mavpackettype', None)
    return result
