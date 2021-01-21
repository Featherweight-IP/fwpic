'''
Created on Jan 20, 2021

@author: mballance
'''
import cocotb
import pybfms
from fwpic_tests.test_base import TestBase


class RegAccess(TestBase):
    
    def __init__(self):
        super().__init__()
        pass
    
    async def run(self):
        u_reg_bfm = pybfms.find_bfm(".*u_reg_bfm")
        
        await u_reg_bfm.write(0x0, 0xaa)
        data = await u_reg_bfm.read(0x0)
        print("data=" + hex(data))
        
        await cocotb.triggers.Timer(10, 'us')
        pass
    
   
@cocotb.test()
async def test(top):
    await pybfms.init()
    t = RegAccess()
    await t.run()
    
    