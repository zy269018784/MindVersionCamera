#include "IVmSolution.h"
#include "VMException.h"
#include "IVmProcedure.h"

using namespace VisionMasterSDK;
using namespace VisionMasterSDK::VmSolution;
using namespace VisionMasterSDK::VmProcedure;

int main(void)
{
    try
    {
        //创建方案单例，用于初始化资源，方案对象可用于注册回调函数/事件等操作
        IVmSolution* pVmSol = CreateSolutionInstance();

        //获取已存在的方案对象，用于跨类操作方案
        pVmSol = GetSolutionExistedInstance();

        //加载方案，仅支持绝对路径，编码格式UTF-8
        pVmSol = LoadSolution("D:\\test.sol", "");
        if (NULL == pVmSol) return IMVS_EC_NULL_PTR;

        //获取方案版本号 
        string strVersion = pVmSol->GetSolutionVersion();

        //判断方案是否加密
        bool bPassword = pVmSol->HasPassword();

        //获取当前方案路径
        string strPath = pVmSol->GetSolutionPath();

        //使用流程名称获取流程对象
        IVmProcedure* pVmPrc = (IVmProcedure*)(*pVmSol)["流程1"];

        //获取方案所有流程对象
        ObjectList procedureObjList = pVmSol->GetAllProcedureObjects();

        //获取方案所有流程信息
        ProcessInfoList* procedureList = pVmSol->GetAllProcedureList();

        //获取方案所有模块信息
        ModuleInfoList* moduInfoList = pVmSol->GetAllModuleList();

        //使用流程名称禁用流程，禁用后流程不参与方案运行
        pVmSol->DisableProcedure("流程1");

        //使用流程名称启用流程
        pVmSol->EnableProcedure("流程1");

        //使用流程名称删除流程
        pVmSol->DeleteOneProcedure("流程2");

        //禁用方案所有流程/Group/模块回调，可提高运行效率，降低CPU资源依赖
        //注意若需获取流程/Group/模块输出，还需单独启用对应流程/Group/模块的回调
        pVmSol->DisableModulesCallback();
        pVmPrc->EnableResultCallback();

        //启用方案所有流程/Group/模块回调
        pVmSol->EnableModulesCallback();

        //方案同步执行一次
        pVmSol->Run();

        //设置连续执行时间间隔
        pVmSol->SetRunInterval(500);

        //方案开始连续执行
        pVmSol->Runing();

        //方案停止连续执行
        pVmSol->StopRun();

        //保存当前方案
        pVmSol->SaveSolution();

        //方案另存为
        pVmSol->SaveAsSolution("D:\\Test1.sol", "");

        //关闭当前方案
        DestroySolutionInstance(pVmSol);

        //退出程序前释放所有资源，注意避免在析构函数中调用
        DisposeResource();
    }
    catch (CVmException vmex)
    {
        return vmex.GetErrorCode();
    }
    catch (...)
    {
        return IMVS_EC_UNKNOWN;
    }

    return IMVS_EC_OK;
}
